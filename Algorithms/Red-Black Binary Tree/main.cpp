#pragma once
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <ctime>

#include "DynamicArray.h"

#pragma execution_character_set("utf-8")
using namespace std;
//
// ===================================================================
//
template <typename T> class Node {
public:
	Node* parent{};
	Node* right{};
	Node* left{};

	T data{};

	int key{};
	bool isRed{ true };

	explicit Node(T data)
		: data(data) {}
};
//
// ===================================================================
//
template <typename T> class RedBlackTree {
private:
	Node<T>* root_{};
	int size_{};
	//
	// ===================================================================================
	//
	void insert_node(T data)
	{
		Node<T>* node = new_node(data, true);

		// Check whether tree is Empty
		if (root_ == nullptr) {
			// If tree is Empty then insert new_node as root_ with isRed = false and exit from the operation
			root_ = node;
			node->isRed = false;
			return;
		}

		// If tree is not Empty then insert new_node as a leaf node with isRed == true
		Node<T>* current = root_;
		Node<T>* parent = nullptr;

		while (current) {
			parent = current;
			if (*node->data < *current->data)
				current = current->left;
			else
				current = current->right;
		}
		node->parent = parent;

		if (*node->data < *parent->data)
			parent->left = node;
		else
			parent->right = node;

		insertion_fix(node);
	}

	void insertion_fix(Node<T>* node)
	{
		Node<T>* uncle = nullptr;
		// If new_node->parent->isRed == false then exit from the operation
		while (node->parent->isRed == true)
		{
			if (node->parent == node->parent->parent->left)
			{
				uncle = node->parent->parent->right;
				// If new_node->parent->isRed == true then check isRed of new_node's uncle
				if (uncle && uncle->isRed == true)
				{
					// If uncle->isRed == true then perform Recolor and Recheck it. Repeat the same until tree becomes Red Black Tree
					uncle->isRed = false;
					node->parent->isRed = false;
					node->parent->parent->isRed = true;
					node = node->parent->parent;
				}
				else {
					// If uncle->isRed == false or nullptr then make a suitable Rotation and Recolor it
					if (node == node->parent->right)
					{
						node = node->parent;
						left_rotate(node);
					}
					node->parent->isRed = false;
					node->parent->parent->isRed = true;
					right_rotate(node->parent->parent);
				}
			}
			else if (node->parent == node->parent->parent->right)
			{
				uncle = node->parent->parent->left;
				// If new_node->parent->isRed == true then check isRed of new_node's uncle
				if (uncle && uncle->isRed == true)
				{
					// If uncle->isRed == true then perform Recolor and Recheck it. Repeat the same until tree becomes Red Black Tree
					uncle->isRed = false;
					node->parent->isRed = false;
					node->parent->parent->isRed = true;
					node = node->parent->parent;
				}
				else {
					// If uncle->isRed == false or nullptr then make a suitable Rotation and Recolor it
					if (node == node->parent->left)
					{
						node = node->parent;
						right_rotate(node);
					}
					node->parent->isRed = false;
					node->parent->parent->isRed = true;
					left_rotate(node->parent->parent);
				}
			}
			if (node == root_)
				break;
		}
		root_->isRed = false;
	}

	void left_rotate(Node<T>* p)
	{
		Node<T>* rc = p->right;
		p->right = rc->left;

		if (rc->left != nullptr)
			rc->left->parent = p;

		rc->parent = p->parent;

		if (p->parent == nullptr)
			root_ = rc;
		else if (p == p->parent->left)
			p->parent->left = rc;
		else
			p->parent->right = rc;

		rc->left = p;
		p->parent = rc;
	}

	void right_rotate(Node<T>* p)
	{
		Node<T>* lc = p->left;
		p->left = lc->right;

		if (lc->right != nullptr)
			lc->right->parent = p;

		lc->parent = p->parent;

		if (p->parent == nullptr)
			root_ = lc;
		else if (p == p->parent->right)
			p->parent->right = lc;
		else
			p->parent->left = lc;

		lc->right = p;
		p->parent = lc;
	}

	Node<T>* new_node(T data, bool isRed)
	{
		Node<T>* new_node = new Node<T>(data);
		size_++;

		new_node->isRed = isRed;
		new_node->key = size_;

		return new_node;
	}
	//
	// ===================================================================================
	//
	Node<T>* find(T data, Node<T>* root)
	{
		if (root == nullptr || *data == *root->data)
			return root;

		if (*data > *root->data)
			return find(data, root->right);
		return find(data, root->left);
	}

	int get_depth(Node<T>* root)
	{
		if (!root) return 0;

		const int left_depth = get_depth(root->left);
		const int right_depth = get_depth(root->right);

		const int depth = 1 + max(left_depth, right_depth);

		return depth;
	}

	void pre_order_traversal(Node<T>* root, DynamicArray<Node<T>*>& array)
	{
		if (!root) return;

		array.append(root);
		pre_order_traversal(root->left, array);
		pre_order_traversal(root->right, array);
	}

	void in_order_traversal(Node<T>* root, DynamicArray<Node<T>*>& array)
	{
		if (!root) return;

		in_order_traversal(root->left, array);
		array.append(root);
		in_order_traversal(root->right, array);
	}

	void delete_node(Node<T>*& root)
	{
		if (!root)
			return;

		delete_node(root->left);
		delete_node(root->right);

		size_--;
		delete root;
		root = nullptr;
	}

public:

	void insert(T data)
	{
		insert_node(data);
	}

	Node<T>* find(T data)
	{
		return find(data, root_);
	}

	int get_depth()
	{
		return get_depth(root_);
	}

	void in_order_traversal(DynamicArray<Node<T>*>& array)
	{
		in_order_traversal(root_, array);
	}

	void pre_order_traversal(DynamicArray<Node<T>*>& array)
	{
		pre_order_traversal(root_, array);
	}

	string to_string(const int nodes_amount = 0)
	{
		ostringstream array_string;
		const int depth = get_depth();
		array_string
			<< "┏━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━┓\n"
			<< left << setw(25) << "┃Tree size"
			<< "┃" << setw(22) << size_ << "┃\n"
			<< setw(25) << "┃Tree depth"
			<< "┃" << setw(22) << depth << "┃\n"
			<< setw(25) << "┃Tree log"
			<< "┃" << setw(22) << depth / log2(size_ + 1) << "┃\n"
			<< "┗━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━┛\n";

		if (size_ == 0) return array_string.str();

		const int max_index = nodes_amount == 0 ? min(size_, 10) : min(size_, nodes_amount);

		auto* pre_order_array = new DynamicArray<Node<T>*>();
		pre_order_traversal(*pre_order_array);

		array_string << "{\n";
		for (int i = 0; i < max_index; i++) {
			Node<T>* node = pre_order_array->operator[](i);

			string parent_node = (node->parent == nullptr) ? "NULL" : (std::to_string(node->parent->key));
			string left_node = (node->left == nullptr) ? "NULL" : (std::to_string(node->left->key));
			string right_node = (node->right == nullptr) ? "NULL" : (std::to_string(node->right->key));
			string color = (node->isRed == true) ? "red" : "black";

			array_string << "\t(" << node->key << ": "
				<< "[" << color << ", p: " << parent_node << ", l: " << left_node
				<< ", r: " << right_node
				<< "], data: " << *node->data << "),\n";
		}
		array_string << "}\n";

		for (size_t i = 0; i < pre_order_array->get_size(); i++)
			pre_order_array->operator[](i) = nullptr;

		delete pre_order_array;

		return array_string.str();
	}

	void clear()
	{
		delete_node(root_);
	}
};
//
// ===================================================================
//
int my_rand(const int rand_num) {
	int x = rand();
	x <<= 15;
	x ^= rand();
	x %= rand_num + 1;
	return x;
}
//
// ===================================================================
//
int main()
{
	srand(time(NULL));
	SetConsoleOutputCP(65001);

	constexpr int MAX_ORDER = 7;
	auto* rbt = new RedBlackTree< int* >();

	for (int o = 1; o <= MAX_ORDER; o++) {
		const int n = pow(10, o);

		clock_t t1 = clock();
		for (int i = 0; i < n; i++)
		{
			int* num = new int(my_rand(n * 2));
			rbt->insert(num);
		}
		clock_t t2 = clock();

		const double exec_time = (t2 - t1) / static_cast<double>(CLOCKS_PER_SEC) * 1000;
		cout
			<< rbt->to_string()
			<< "Exec. Time: " << exec_time << " ms" << endl;


		const int m = pow(10, 4);
		int hits = 0;
		t1 = clock();
		for (int i = 0; i < m; i++)
		{
			int* num = new int(my_rand(n * 2));
			auto* result = rbt->find(num);
			if (result != NULL)
				hits++;
			delete num;
		}
		t2 = clock();

		const double finding_time = (t2 - t1) / static_cast<double>(CLOCKS_PER_SEC) * 1000;
		cout
			<< "Hits: " << hits
			<< "\nFinding Time: " << finding_time << " ms" << endl;

		rbt->clear();
		cout << "Tree is cleared.\n" << endl;
	}
	delete rbt;
	return 0;
}