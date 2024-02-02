// ALGO2 IS1 210B LAB05
// Stanislav Tkachenko
// ts54948@zut.edu.pl
#pragma once
#include <iostream>
#include <string>

#pragma execution_character_set("utf-8")
using namespace std;
//
// ===================================================================
//
template <typename T>
class Heap
{
	int size{};
	int capacity{};
	T* array;
	int (*cmp)(T, T);
	bool direction{};

	void overwrite_array()
	{
		T* temp_array = new T[capacity];

		for (int i = 0; i < size; i++)
			temp_array[i] = array[i];

		delete[] array;
		array = temp_array;
	}

public:
	Heap(T* array, const int n, int (*cmp)(T, T), const bool dir)
		: size(n), capacity(n), array(array), cmp(cmp), direction(dir)
	{
		if (direction) // naprawa w gore 
			for (int i = size / 2 - 1; i >= 0; i--)
				heapify_down(size, i);
		else // naprawa w dol
			for (int i = 1; i < size; i++)
				heapify_up(i);
	}

	~Heap()
	{
		while (size > 0)
		{
			delete array[size - 1];
			array[size - 1] = nullptr;
			size--;
		}
		delete[] array;
	}

	void heapify_down(const int length, int index)
	{
		int left_child = 2 * index + 1;
		int right_child = 2 * index + 2;
		int largest = index;

		if (left_child < length && cmp(array[left_child], array[largest]) > 0)
			largest = left_child;

		if (right_child < length && cmp(array[right_child], array[largest]) > 0)
			largest = right_child;

		if (largest != index)
		{
			swap(array[index], array[largest]);
			heapify_down(length, largest);
		}
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

	void sort(const bool dir)
	{
		if (dir)
			sort_down();
		else
			sort_up();
	}

	void sort_down()
	{
		for (int i = size - 1; i > 0; i--) {
			swap(array[0], array[i]);
			heapify_down(i, 0);
		}
	}

	void sort_up()
	{
		for (int i = size - 1; i > 0; i--) {
			swap(array[0], array[i]);

			for (int j = 1; j < i; j++)
				heapify_up(j);
		}
	}

};