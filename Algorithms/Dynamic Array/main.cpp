#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <Windows.h>
#include <cmath>

#pragma execution_character_set( "utf-8" )
using namespace std;

template <typename T>
class DynamicArray
{
	T* array{};
	size_t size{};
	size_t capacity{};

	void overwrite_array()
	{
		T* temp_array = new T[capacity];

		for (size_t i = 0; i < size; i++)
			temp_array[i] = array[i];

		delete[] array;
		array = temp_array;
	}

public:
	DynamicArray() : capacity(1) { array = new T[capacity]; }
	~DynamicArray()
	{
		clear();
		delete[] array;
	}

	size_t get_size() const { return size; }
	size_t get_capacity() const { return capacity; }

	void append(T value)
	{
		if (size == capacity) extend_array();
		array[size] = value;
		size++;
	}

	void pop()
	{
		if (size == 0) throw out_of_range("Pop from empty list.");

		delete array[size - 1];
		array[size - 1] = nullptr;
		size--;

		if (size == capacity / 2) shrink_array();
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

	T& operator[](size_t index)
	{
		if (index >= size)
			throw out_of_range("Index out of range.");

		return array[index];
	}

	void clear()
	{
		while (size > 0)
			pop();
	}

	void bubble_sort(int (*cmp)(T, T))
	{
		bool swapped;
		for (size_t i = 0; i < size - 1; i++)
		{
			swapped = false;
			for (size_t j = 0; j < size - i - 1; j++)
			{
				int cmp_result = cmp(array[j], array[j + 1]);
				if (cmp_result == 1)
				{
					swap(array[j], array[j + 1]);
					swapped = true;
				}
			}
		}
	}

	string to_string(string(*get_elem_data)(T))
	{
		ostringstream array_string;
		array_string
			<< left << setw(25)
			<< "┃List size" << "┃" << setw(22) << size << "┃\n" << setw(25)
			<< "┃List capacity" << "┃" << setw(22) << capacity << "┃\n" << setw(25)
			<< "┃List address" << "┃" << setw(22) << this << "┃\n"
			<< "┣━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━┫";

		if (size == 0)
			return array_string.str();

		for (size_t i = 0; i < min(size, 5); i++)
			array_string << setw(26) << (string("\n┃Element [") + std::to_string(i) + ']') << "┃" << setw(22) << get_elem_data(array[i]) << "┃";

		if (size <= 5)
		{
			array_string << "\n┗━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━┛";
			return array_string.str();
		}

		for (size_t i = size - 5; i < size; i++)
			array_string << setw(26) << (string("\n┃Element [") + std::to_string(i) + ']') << "┃" << setw(22) << get_elem_data(array[i]) << "┃";

		array_string << "\n┗━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━┛";
		return array_string.str();
	}
};

template <typename T>
int num_cmp(T num1, T num2)
{
	if (*num1 > *num2) return 1;
	else if (*num1 < *num2) return -1;
	else return 0;
}
template <typename T>
string get_num_data(T data)
{
	ostringstream object_info;
	object_info << *data;
	return object_info.str();
}

int main()
{
	SetConsoleOutputCP(65001);
	srand(time(NULL));

	DynamicArray < int* >* da = new DynamicArray< int* >();
	const int order = 7;
	const int n = pow(10, order);

	cout << "┏━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━┓\n";

	double max_time_per_element = 0.0;
	clock_t t1 = clock();
	for (size_t i = 0; i < n; i++)
	{
		int* num = new int(rand() % 1000 + 1);

		clock_t t1_element = clock();
		da->append(num);
		clock_t t2_element = clock();

		double time_per_element = (t2_element - t1_element) / (double)CLOCKS_PER_SEC;
		if (time_per_element > max_time_per_element)
		{
			max_time_per_element = time_per_element;
			cout << left << setw(25) << (string("┃Element [") + std::to_string(i) + ']') << "┃" << setw(19) << max_time_per_element * 1000 << " ms┃\n";
		}
	}
	clock_t t2 = clock();
	double exec_time = (t2 - t1) / (double)CLOCKS_PER_SEC;
	cout << "┣━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━┫\n" << setw(25) << left << "┃Execution time" << "┃" << setw(19) << left << exec_time * 1000.0 << " ms┃\n";
	cout << da->to_string(get_num_data) << endl;

	da->clear();
	delete da;
	return 0;
}