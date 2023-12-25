#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <Windows.h>

#pragma execution_character_set( "utf-8" )
using namespace std;

string tab_start = "┏━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━┓\n";
string tab_end = "\n┗━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━┛";
// =======================================================================================================================================================
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
private:
	Node<T>* Head{};
	Node<T>* Tail{};
	size_t size{};

	void add_after_element(Node<T>* current, T data)
	{
		Node<T>* node = new Node<T>();
		node->data = data;

		if (current == Tail)
			add_behind(data);

		node->next = current->next;
		current->next = node;
		node->previous = current;
		node->next->previous = node;
	}

	void add_before_element(Node<T>* current, T data)
	{
		Node<T>* node = new Node<T>();
		node->data = data;

		if (current == Head)
			add_ahead(data);

		node->previous = current->previous;
		current->previous = node;
		node->next = current;
		node->prevoius->next = node;
	}

	void format_string(ostringstream& list_info, size_t i, string(*get_object_info)(T))
	{
		T data = this->operator[](i);
		list_info << left << setw(26) << (string("\n┃Element [") + std::to_string(i) + ']') << "┃" << setw(22) << left << get_object_info(data) << "┃";
	}

public:
	~Linked_list()
	{
		if (size > 0)
			clear();
	}

	T operator[](size_t index)
	{
		if (index < size)
		{
			if (index < ceil(size / 2))
			{
				Node<T>* buffer = Head;
				for (size_t i = 0; i < index; i++) buffer = buffer->next;
				return buffer->data;
			}
			else
			{
				Node<T>* buffer = Tail;
				size_t i_size = size - 1;
				for (size_t i = i_size; i > index; i--) buffer = buffer->previous;
				return buffer->data;
			}
		}
		else throw out_of_range("Out of range.");
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
		++size;
	}
	void add_after(T data, size_t index)
	{
		if (index < size)
		{
			if (index < ceil(size / 2))
			{
				Node<T>* buffer = Head;
				for (size_t i = 0; i < index; i++) buffer = buffer->next;
				add_after_element(buffer, data);
			}
			else
			{
				Node<T>* buffer = Tail;
				for (size_t i = size; i >= index; i--) buffer = buffer->previous;
				add_after_element(buffer, data);
			}
		}
	}
	void add_ahead(T data)
	{
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
				node->next = Head;
				Head->previous = node;
				Head = node;
			}
			++size;
		}
	}
	void remove_behind()
	{
		if (size == 1) {
			delete Tail;
			Tail = nullptr;
			Head = nullptr;
		}
		else {
			Tail = Tail->previous;
			delete Tail->next;
			Tail->next = nullptr;
		}
		size--;
	}
	void remove_ahead()
	{
		if (size == 1)
		{
			delete Head;
			Head = nullptr;
			Tail = nullptr;
		}
		else
		{
			Head = Head->next;
			delete Head->previous;
			Head->previous = nullptr;
		}
		--size;
	}
	void clear()
	{
		while (size > 0)
			remove_behind();
	}

	T find_first(T comparand, int (*cmp)(T, T))
	{
		Node<T>* comparator = Head;
		for (size_t i = 0; i < size; i++)
		{
			int result = cmp(comparand, comparator->data);
			if (result == 0) return comparator->data;
			comparator = comparator->next;
		}
		return NULL;
	}
	void add_with_sorting(T data, int(*cmp)(T, T))
	{
		if (size == 0)
			add_behind(data);

		else {
			Node<T>* current = Head;
			while (true)
			{
				if (cmp(data, current->data) < 0) {
					add_before_element(current, data);
					break;
				}
				if (current == Tail) {
					add_behind(data);
					break;
				}
				current = current->next;
			}
		}
	}
	bool find_and_remove(T comparand, int (*cmp)(T, T)) {
		Node<T>* current = Head;

		while (current != nullptr)
		{
			int result = cmp(comparand, current->data);
			if (result == 0)
			{
				if (current->previous != nullptr) current->previous->next = current->next;
				if (current->next != nullptr) current->next->previous = current->previous;
				if (current == Head) Head = current->next;
				if (current == Tail) Tail = current->previous;

				delete current;
				size--;
				return true;
			}
			current = current->next;
		}

		return false;
	}

	string to_string(string(*get_object_info)(T), size_t to_display = 0)
	{
		ostringstream list_info;
		list_info << left << setw(25)
			<< "┃List size" << "┃" << setw(22) << left << size << "┃\n" << setw(25) << left
			<< "┃List address" << "┃" << setw(22) << left << this << "┃\n"
			<< "┣━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━┫";

		if (size == 0)
			return list_info.str();

		to_display = to_display == 0 ? min(size, 5) : 0;

		for (size_t i = 0; i < to_display; i++)
			format_string(list_info, i, get_object_info);

		if (to_display == size)
			return list_info.str();

		for (size_t i = to_display; i > 0; i--)
			format_string(list_info, size - i, get_object_info);

		return list_info.str();
	}
};
// =======================================================================================================================================================
template <typename T>
int number_cmp(T comparand, T comparator)
{
	if (*comparand > *comparator) return 1;
	if (*comparand < *comparator) return -1;
	return 0;
}

template <typename T>
string get_number_info(T data)
{
	ostringstream object_info;
	object_info << *data;
	return object_info.str();
}

void print_time(const double time)
{
	cout.precision(6);
	cout << tab_start << setw(25) << left
		<< "┃Execution time" << "┃" << setw(19) << left << time * 1000.0 << " ms" << "┃\n";
	cout.precision(2);
}

int my_rand(const int rand_num) {
	int x = rand();
	x <<= 15;
	x ^= rand();
	x %= rand_num + 1;
	return x;
}
// =======================================================================================================================================================
void test_int()
{
	constexpr int MAX_ORDER = 6;

	Linked_list < int* >* ll = new Linked_list < int* >();
	// ============================================================================
	for (int o = 0; o <= MAX_ORDER; o++)
	{
		const int n = static_cast<int>(pow(10, o));
		clock_t t1 = clock();
		for (int i = 0; i < n; i++)
		{
			int* num = new int(my_rand(n * 2));
			ll->add_behind(num);
		}
		clock_t t2 = clock();
		double time = (t2 - t1) / static_cast<double>(CLOCKS_PER_SEC);

		cout << "List of 10^" << o << " elements" << endl;
		print_time(time);
		cout << ll->to_string(get_number_info) << tab_end << endl;
		// ============================================================================
		const int m = static_cast<int>(pow(10, 4));
		t1 = clock();
		for (int i = 0; i < m; i++)
		{
			int* num = new int(my_rand(n * 2));
			ll->find_and_remove(num, number_cmp);
			delete num;
		}
		t2 = clock();
		time = (t2 - t1) / static_cast<double>(CLOCKS_PER_SEC);

		print_time(time);
		cout << ll->to_string(get_number_info) << tab_end << "\n" << endl;
		// ============================================================================
		ll->clear();
	}
	delete ll;
}

int main()
{
	SetConsoleOutputCP(65001);
	srand(static_cast<unsigned int>(time(nullptr)));

	test_int();
	return 0;
}