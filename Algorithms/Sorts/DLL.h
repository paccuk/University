#pragma once
#include <iostream>

using namespace std;

template <typename T>
struct Node
{
public:
	T data{};
	Node* next{};
	Node* previous{};

	~Node()
	{
		delete data;
		data = nullptr;
	}
};

template <typename T>
struct Linked_list
{
public:
	Node<T>* Head{};
	Node<T>* Tail{};
	size_t size{};

	~Linked_list()
	{
		while (size > 0)
			remove_behind();
	}

	void add_behind(T data)
	{
		Node<T>* node = new Node<T>();
		node->data = data;

		if (size == 0)
		{
			Head = node;
			Tail = node;
		}
		else
		{
			Tail->next = node;
			node->previous = Tail;
			Tail = node;
		}
		size++;
	}

	void remove_behind()
	{
		if (size == 1)
		{
			delete Tail;
			Tail = nullptr;
			Head = nullptr;
		}
		else
		{
			Tail = Tail->previous;
			delete Tail->next;
			Tail->next = nullptr;
		}
		size--;
	}

	void sort_add(T data, int (*cmp)(T, T))
	{
		if (size == 0)
			add_behind(data);

		else
		{
			Node<T>* current = Head;

			while (current) {
				if (cmp(data, current->data) < 0)
				{
					if (current == Head) {
						Node<T>* node = new Node<T>();
						node->data = data;
						node->next = current;
						current->previous = node;
						Head = node;
					}
					else {
						Node<T>* node = new Node<T>();
						node->data = data;
						node->previous = current->previous;
						node->next = current;
						current->previous->next = node;
						current->previous = node;
					}
					break;
				}
				if (current == Tail) {
					Node<T>* node = new Node<T>();
					node->data = data;
					node->previous = current;
					current->next = node;
					Tail = node;
					break;
				}
				current = current->next;
			}
		}
	}
};