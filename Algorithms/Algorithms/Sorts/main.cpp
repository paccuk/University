#pragma once
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <cmath>

#include "Heap.h"
#include "DLL.h"

using namespace std;
//
// ===================================================================
//
class Book
{
public:
	string title{};
	string author{};
	int year{};
	int pages{};
	double price{};

	friend ostream& operator<<(ostream& os, const Book& book)
	{
		os << book.price;
		return os;
	}
};

template <typename T>
int book_cmp(T b1, T b2)
{
	if (b1->price > b2->price)
		return 1;
	if (b1->price < b2->price)
		return -1;
	return 0;
}

template <typename T>
double book_key_double(T book)
{
	return book->price;
}
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

void set_cout_color(const WORD attr)
{
	SetConsoleTextAttribute(GetStdHandle(-11), attr);
}

void set_def_cout_color()
{
	SetConsoleTextAttribute(GetStdHandle(-11), 0x07);
}

void print_separator()
{
	cout << "------------------------------------------------------<|";
}

void compare_arrays(const int n, const int* array1, const int* array2, const int* array3 = nullptr)
{
	for (int i = 0; i < n; i++)
		if (array1[i] != array2[i])
		{
			set_cout_color(0x0C);
			cout << "\nArrays 1 and 2 are not equal!\n";
			set_def_cout_color();
			cout << "[" << i << "] " << array1[i] << " != " << array2[i] << endl;
		}

	if (array3 != nullptr) {
		for (int i = 0; i < n; i++)
			if (array1[i] != array3[i])
			{
				set_cout_color(0x0C);
				cout << "Arrays 1 and 3 are not equal!\n";
				set_def_cout_color();
				cout << "[" << i << "] " << array1[i] << " != " << array2[i] << endl;
			}

		for (int i = 0; i < n; i++)
			if (array2[i] != array3[i])
			{
				set_cout_color(0x0C);
				cout << "Arrays 2 and 3 are not equal!\n";
				set_def_cout_color();
				cout << "[" << i << "] " << array2[i] << "!=" << array2[i] << endl;
				return;
			}
	}

	set_cout_color(0x0A);
	cout << "\nArrays are equal!" << endl;
	set_def_cout_color();

}

template <typename T>
void compare_arrays(const int length, T* array1, T* array2, int (*cmp)(T, T))
{
	for (int i = 0; i < length; i++)
		if (cmp(array1[i], array2[i]) != 0)
		{
			set_cout_color(0x0C);
			cout << "\nArrays are not equal!" << endl;
			set_def_cout_color();
			return;
		}

	set_cout_color(0x0A);
	cout << "\nArrays are equal!" << endl;
	set_def_cout_color();
}
//
// ===================================================================
//
void print_array(const int* array, const int length, const int to_print, const string& name)
{
	cout << name << " (" << length << " elements):\n";

	if (to_print >= 0)
		for (int i = 0; i < min(to_print, length); i++)
			cout << setw(4) << "[" << i << "] " << array[i] << "\n";
	else
		for (int i = length - 1; i >= max(length + to_print, 0); i--)
			cout << setw(4) << "[" << i << "] " << array[i] << "\n";
}

void print_array(Book** array, const int length, const int to_print, const string& name)
{
	cout << name << " (" << length << " elements):\n";

	cout.precision(10);
	for (int i = 0; i < min(to_print, length); i++)
		cout << setw(4) << "[" << i << "] " << *array[i] << "\n";

	cout.precision(7);
}

void print_time(const clock_t t1, const clock_t t2, const string& name)
{
	cout << "\n"
		<< name << ": " << (t2 - t1) / static_cast<double>(CLOCKS_PER_SEC) * 1000 << " ms" << endl;
}
//
// ===================================================================
//
void counting_sort(int* array, const int n, const int m)
{
	int* counters = new int[m + 1];

	for (int i = 0; i < m + 1; i++)
		counters[i] = 0;

	for (int i = 0; i < n; i++)
		counters[array[i]]++;

	int index = 0;
	for (int i = 0; i < m + 1; i++)
		while (counters[i] > 0)
		{
			array[index] = i;
			counters[i]--;
			index++;
		}

	delete[] counters;
}

void bucket_sort(int* array, const int n, const int m)
{
	Linked_list<int>** buckets = new Linked_list<int>*[n];

	for (int i = 0; i < n; i++)
		buckets[i] = new Linked_list<int>();

	for (int i = 0; i < n; i++)
	{
		const int index = static_cast<size_t>(array[i]) * n / (m + 1);
		buckets[index]->sort_add(array[i], cmp_ints);
	}

	int index = 0;
	for (int i = 0; i < n; i++)
	{
		const Node<int>* current = buckets[i]->Head;
		while (current)
		{
			array[index++] = current->data;
			current = current->next;
		}
		// delete buckets[i];
	}
	delete[] buckets;
}

template <typename T>
void bucket_sort(T* array, const int n, const double m, double (*key)(T), int (*cmp)(T, T))
{
	Linked_list<T>** buckets = new Linked_list<T>*[n];

	for (int i = 0; i < n; i++)
		buckets[i] = new Linked_list<T>();
	double w = m / n;
	for (int i = 0; i < n; i++)
	{
		const int index = static_cast<int>(key(array[i]) / w);
		buckets[index]->sort_add(array[i], cmp);
	}

	int index = 0;
	for (int i = 0; i < n; i++)
	{
		const Node<T>* current = buckets[i]->Head;
		while (current)
		{
			array[index++] = current->data;
			current = current->next;
		}
	}
	delete[] buckets;
}
//
// ===================================================================
//
void main_ints()
{
	constexpr int MAX_ORDER = 7;
	const int m = static_cast<int>(pow(10, 7));

	for (int o = 1; o <= MAX_ORDER; o++)
	{
		const int n = static_cast<int>(pow(10, o));
		int* array1 = new int[n];

		clock_t t1 = clock();
		for (int i = 0; i < n; i++)
		{
			const int rand_val = my_rand(m);
			array1[i] = rand_val;
		}
		clock_t t2 = clock();

		print_separator();
		print_time(t1, t2, "Creating time");
		print_array(array1, n, 16, "Unsorted array1");


		int* array2 = new int[n];
		int* array3 = new int[n];
		memcpy(array2, array1, n * sizeof(int));
		memcpy(array3, array1, n * sizeof(int));

		// -----------------------------------------------------
		// sortowanie przez zliczanie ( do wykonania w miejscu )
		t1 = clock();
		counting_sort(array1, n, m);
		t2 = clock();

		print_time(t1, t2, "Sorting time");
		print_array(array1, n, 16, "Counting sort array1");

		// -----------------------------------------------------
		// sortowanie przez kopcowanie ( do wykonania w miejscu )
		t1 = clock();
		Heap<int>* bh = new Heap<int>(array2, n, cmp_ints, true);
		bh->sort(true);
		t2 = clock();

		print_time(t1, t2, "Sorting time");
		print_array(array2, n, 16, "Heap sort array2");

		// -----------------------------------------------------
		// sortowanie kubelkowe ( do wykonania w miejscu )
		t1 = clock();
		bucket_sort(array3, n, m);
		t2 = clock();

		print_time(t1, t2, "Sorting time");
		print_array(array3, n, 16, "Bucket sort array3");

		compare_arrays(n, array1, array2, array3);

		delete[] array1;
		delete[] array2;
		delete[] array3;
	}
}

void main_some_objects()
{
	constexpr int MAX_ORDER = 7;
	const double m_double = pow(2, 30);

	for (int o = 1; o <= MAX_ORDER; o++)
	{
		const int n = static_cast<int>(pow(10, o));
		Book** array1 = new Book * [n];

		clock_t t1 = clock();
		for (int i = 0; i < n; i++)
		{
			Book* book = new Book();
			book->price = ((rand() << 15) + rand()) / m_double;
			book->title = 'a' + rand() % 26;
			array1[i] = book;
		}
		clock_t t2 = clock();

		print_separator();
		print_time(t1, t2, "Creating time");
		print_array(array1, n, 16, "array1");

		Book** array2 = new Book * [n];
		memcpy(array2, array1, n * sizeof(Book*));

		// -----------------------------------------------------
		// sortowanie przez kopcowanie
		t1 = clock();
		Heap<Book*>* bh = new Heap<Book*>(array1, n, book_cmp, true);
		bh->sort(true);
		t2 = clock();

		print_time(t1, t2, "Sorting time");
		print_array(array1, n, 16, "array1");

		// -----------------------------------------------------
		// sortowanie kubelkowe
		t1 = clock();
		bucket_sort(array2, n, 1.0, book_key_double, book_cmp);
		t2 = clock();

		print_time(t1, t2, "Sorting time");
		print_array(array2, n, 16, "array2");

		compare_arrays(n, array1, array2, book_cmp);

		delete[] array1;
		delete[] array2;
	}
}

int main()
{
	srand(static_cast<unsigned>(time(nullptr)));
	main_ints();
	// main_some_objects();
	return 0;
}