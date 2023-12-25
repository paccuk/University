#pragma once
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <ctime>
#include <cmath>

#pragma execution_character_set("utf-8")
using namespace std;
//
// ===================================================================
//
template <typename T>
class Heap
{
	int size, capacity;
	T *array;
	int (*cmp)(T, T);
	bool direction;

	void overwrite_array()
	{
		T *temp_array = new T[capacity];

		for (int i = 0; i < size; i++)
			temp_array[i] = array[i];

		delete[] array;
		array = temp_array;
	}

public:
	Heap(int (*cmp)(T, T))
		: size(0), capacity(1), array(new T[capacity]), cmp(cmp)
	{
	}

	Heap(T *array, const int n, int (*cmp)(T, T), bool direction)
		: size(n), capacity(n), array(array), cmp(cmp), direction(direction)
	{
	}

	~Heap()
	{
		clear();
		delete[] array;
	}

	void add(T data)
	{
		if (size == capacity)
			extend_array();

		array[size] = data;

		heapify_up(size);

		size++;
	}

	T poll()
	{
		if (size == 0)
			throw out_of_range("Pop from empty list.");

		T polled = array[0];
		array[0] = array[size - 1];
		array[size - 1] = nullptr;
		size--;

		heapify_down(0);

		if (size == capacity / 2)
			shrink_array();

		return polled;
	}

	void extend_array()
	{
		capacity *= 2;
		overwrite_array();
	}

	void shrink_array()
	{
		capacity = size;
		overwrite_array();
	}

	void heapify_up(int index)
	{
		if (index == 0)
			return;

		int parent = (index - 1) / 2;

		if (index <= size && cmp(array[index], array[parent]) > 0)
		{
			swap(array[index], array[parent]);
			heapify_up(parent);
		}
	}

	void heapify_down(int index)
	{
		int left_child = 2 * index + 1;
		int right_child = 2 * index + 2;
		int largest = index;

		if (left_child < size && cmp(array[left_child], array[largest]) > 0)
			largest = left_child;

		if (right_child < size && cmp(array[right_child], array[largest]) > 0)
			largest = right_child;

		if (largest != index)
		{
			swap(array[index], array[largest]);
			heapify_down(largest);
		}
	}

	void clear()
	{
		while (size > 0)
			pop();
		delete[] array;

		capacity = 1;
		array = new T[capacity];
	}

	void pop()
	{
		if (size == 0)
			throw out_of_range("Pop from empty list.");

		delete array[size - 1];
		array[size - 1] = nullptr;
		size--;

		if (size == capacity / 2)
			shrink_array();
	}

	string to_string()
	{
		ostringstream array_string;
		array_string
			<< left << setw(25)
			<< "┃List size"
			<< "┃" << setw(22) << size << "┃\n"
			<< setw(25)
			<< "┃List capacity"
			<< "┃" << setw(22) << capacity << "┃\n"
			<< "┣━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━┫";

		if (size == 0)
			return array_string.str();

		for (size_t i = 0; i < min(size, 5); i++)
			array_string << setw(26) << (string("\n┃Element [") + std::to_string(i) + ']') << "┃" << setw(22) << *array[i] << "┃";

		if (size <= 5)
		{
			array_string << "\n┗━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━┛";
			return array_string.str();
		}

		for (size_t i = size - 5; i < size; i++)
			array_string << setw(26) << (string("\n┃Element [") + std::to_string(i) + ']') << "┃" << setw(22) << *array[i] << "┃";

		array_string << "\n┗━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━┛";
		return array_string.str();
	}

	void sort()
	{
		if (direction == true)
			sort_down_top();
		else
			sort_top_down();
	}

	void sort_down_top() // sort all array using heapify_up
	{
		for (int i = 0; i < size; i++)
			heapify_up(i);
	}

	void sort_top_down()
	{
		for (int i = size / 2 - 1; i >= 0; i--)
			heapify_down(i, size);

		for (int i = size - 1; i > 0; i--)
		{
			swap(array[0], array[i]);
			heapify_down(0, i);
		}
	}
};
//
// ===================================================================
//
int my_rand(const int rand_num)
{
	int x = rand();
	x <<= 15;
	x ^= rand();
	x %= rand_num + 1;
	return x;
}

template <typename T>
int cmp_ints(const T a, const T b)
{
	return a - b;
}

template <typename T>
int cmp_ints_ptr(const T a, const T b)
{
	return *a - *b;
}

template <typename T>
void print_polled(T polled)
{
	cout << *polled << "\n";
}

void print_time(const clock_t t1, const clock_t t2, const string &time_type)
{
	const double exec_time = (t2 - t1) / static_cast<double>(CLOCKS_PER_SEC);
	cout << "┏━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━┓\n"
		 << setw(25) << left
		 << ("┃" + time_type + " time") << "┃" << setw(19) << left << exec_time * 1000.0 << " ms┃\n";
}
void print_execution_time(const clock_t t1, const clock_t t2)
{
	print_time(t1, t2, "Execution");
}
void print_polling_time(const clock_t t1, const clock_t t2)
{
	print_time(t1, t2, "Polling");
	cout << "┗━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
}
//
// ===================================================================
//
int main()
{
	SetConsoleOutputCP(65001);
	srand(static_cast<unsigned>(time(nullptr)));

	constexpr int MAX_ORDER = 7;
	auto *heap = new Heap<int *>(cmp_ints_ptr);

	for (int o = 1; o <= MAX_ORDER; o++)
	{
		const int n = static_cast<int>(pow(10, o));

		clock_t t1 = clock();
		for (int i = 0; i < n; i++)
		{
			int *num = new int(my_rand(n * 2));
			heap->add(num);
		}
		clock_t t2 = clock();

		print_execution_time(t1, t2);
		cout << heap->to_string() << endl;

		t1 = clock();
		for (int i = 0; i < n; i++)
		{
			int *polled = heap->poll();
			// print_polled(polled);
			delete polled;
		}
		t2 = clock();
		print_polling_time(t1, t2);

		heap->clear();
	}
	delete heap;
	return 0;
}