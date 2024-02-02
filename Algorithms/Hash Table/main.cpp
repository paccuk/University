#pragma once
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <ctime>

#include "DLL.h"

#pragma execution_character_set( "utf-8" )
using namespace std;
//
// ===================================================================
//
template <typename Kt, typename Vt>
struct Pair {
public:
	Kt key;
	Vt value;

	Pair(Kt key, Vt value)
		: key(key), value(value) {}
};

template <typename Kt, typename Vt>
class HashTable
{
	int size, capacity;
	Linked_list< Pair<Kt, Vt>* >** array;

	void overwrite_array() {
		Linked_list< Pair<Kt, Vt>* >** temp_array = new Linked_list< Pair<Kt, Vt>* >* [capacity];

		initialize_lists(temp_array);

		const int temp_size = size;
		size = 0;

		for (int i = 0; i < temp_size; i++) {
			if (array[i]->size == 0)
				continue;

			Node< Pair<Kt, Vt>* >* current = array[i]->Head;

			while (current != nullptr) {
				put_helper(current->data->key, current->data->value, temp_array);
				current = current->next;
			}
		}
		delete[] array;
		array = temp_array;
	}

	void put_helper(Kt key, Vt value, Linked_list< Pair<Kt, Vt>* >** arr) {
		int hashed_key = hash_key(key); // haszowanie klucza
		Linked_list< Pair<Kt, Vt>* >* found_result = find_pair(hashed_key, arr); // wyszukiwanie pary

		if (found_result == nullptr) { // dodac pare jeszli lista pod indeksem hashed_key jest pusta
			arr[hashed_key]->add_behind(new Pair<Kt, Vt>(key, value));
			size++;
			return;
		}

		Node< Pair<Kt, Vt>* >* current = found_result->Head; // zamienic wartosc w liście z takim samym kluczem

		while (current != nullptr) {
			if (current->data->key == key) {
				current->data->value = value;
				return;
			}
			current = current->next;
		}

		arr[hashed_key]->add_behind(new Pair<Kt, Vt>(key, value)); // dodac nowy pare do listy pod indeksem hashed_key
		size++;
	}

public:
	HashTable() :
		size(0),
		capacity(8),
		array(new Linked_list< Pair<Kt, Vt>* >* [capacity])
	{
		initialize_lists(array);
	}

	void put(Kt key, Vt value) {
		if (size >= round(capacity * 0.75)) // sprawdzenie na wiekszosc
			extend_array(); // zwiekszyc list

		put_helper(key, value, array); // funkcja dla dodawania
	}

	void extend_array() {
		capacity *= 2;
		overwrite_array(); // przepisac liste
	}

	Linked_list< Pair<Kt, Vt>* >* create_list(Kt key, Vt value) {
		Linked_list<Pair<Kt, Vt>*>* list = new Linked_list<Pair<Kt, Vt>*>();
		list->add_behind(new Pair<Kt, Vt>(key, value));

		return list;
	}

	int hash_key(Kt key) {
		return hash_str(key);
	}

	int hash_str(const string& key) {
		const int length = static_cast<int>(key.length());
		int pre_hashing_sum = 0;

		for (int i = 0; i < length; i++)
			pre_hashing_sum += static_cast<int>(static_cast<int>(key[i]) * pow(31, length - i - 1));

		const int hashed_str = mod(pre_hashing_sum, capacity);
		return hashed_str;
	}

	int mod(const int x, const int m) {
		return (x % m + m) % m;
	}

	Linked_list< Pair<Kt, Vt>* >* find_pair(const int index, Linked_list< Pair<Kt, Vt>* >** arr) {
		if (arr[index]->size != 0)
			return arr[index];

		return nullptr;
	}

	void shrink_array() {
		capacity = size;
		overwrite_array();
	}

	Pair<string, int>* get(Kt key) {
		int hashed_key = hash_key(key);
		Linked_list< Pair<Kt, Vt>* >* found_result = find_pair(hashed_key, array);

		if (found_result == nullptr)
			return nullptr;

		Node< Pair<Kt, Vt>* >* current = found_result->Head;
		while (current != nullptr) {
			if (current->data->key == key)
				return current->data;

			current = current->next;
		}
		return nullptr;
	}

	bool remove(Kt key) {
		int hashed_key = hash_key(key);
		Linked_list< Pair<Kt, Vt>* >* found_result = find_pair(hashed_key);

		if (found_result != nullptr) {
			Node< Pair<Kt, Vt>* >* current = found_result->Head;

			while (current != nullptr) {
				if (current->data->key == key) {
					if (current->previous != nullptr) current->previous->next = current->next;
					if (current->next != nullptr) current->next->previous = current->previous;
					if (current == found_result->Head) found_result->Head = current->next;
					if (current == found_result->Tail) found_result->Tail = current->previous;

					delete current;
					size--;
					return true;
				}
				current = current->next;
			}
		}
		return false;
	}

	string to_string(string(*get_elem_data)(Linked_list< Pair<Kt, Vt>* >*))
	{
		ostringstream array_string;
		array_string
			<< left << setw(25)
			// << "┏━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━┓\n" << setw(25) << left
			<< "┃Table size" << "┃" << setw(22) << size << "┃\n" << setw(25)
			<< "┃Table capacity" << "┃" << setw(22) << capacity << "┃\n"
			<< "┗━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━┛\n";

		if (size == 0)
			return array_string.str();

		array_string << "{";
		for (int i = 0; i < min(capacity, 10); i++)
			array_string << "\n\t" << i << ": " << get_elem_data(array[i]);

		array_string << "\n}";
		return array_string.str();
	}

	void print_stats() {
		cout << "\nstats:\n"
			<< "\tlist min size: " << get_min_size() << "\n"
			<< "\tlist max size: " << get_max_size() << "\n"
			<< "\tnot-null lists: " << get_not_null_lists() << "\n"
			<< "\tlist avg size: " << get_list_avg_size() << endl;
	}

	size_t get_min_size() {
		size_t min_size = get_max_size();
		size_t temp_size = 0;

		for (int i = 0; i < capacity; i++) {
			temp_size = array[i]->size;
			if (temp_size < min_size && temp_size > 0)
				min_size = temp_size;
		}
		return min_size;
	}

	size_t get_max_size() {
		size_t max_size = 0;
		size_t temp_size = 0;

		for (int i = 0; i < capacity; i++) {
			temp_size = array[i]->size;
			if (temp_size > max_size)
				max_size = temp_size;
		}
		return max_size;
	}

	int get_not_null_lists() {
		int not_null_lists = 0;

		for (int i = 0; i < capacity; i++) {
			if (array[i]->size > 0)
				not_null_lists++;
		}
		return not_null_lists;
	}

	double get_list_avg_size() {
		size_t list_avg_size = 0;
		double non_empty_lists = 0;

		for (int i = 0; i < capacity; i++) {
			if (array[i]->size > 0) {
				list_avg_size += array[i]->size;
				non_empty_lists++;
			}
		}
		if (non_empty_lists > 0)
			return list_avg_size / non_empty_lists;

		return 0;
	}

	void print_hits_count(const int hits) {
		cout << "Hits: " << hits;
	}

	void clear() {
		for (int i = 0; i < size; i++) {
			delete array[i];
		}
		delete[] array;
		size = 0;
		capacity = 8;
		array = new Linked_list< Pair<Kt, Vt>* >* [capacity];

		initialize_lists(array);
	}

	void initialize_lists(Linked_list< Pair<Kt, Vt>* >** arr) {
		for (int i = 0; i < capacity; i++)
			arr[i] = new Linked_list< Pair<Kt, Vt>* >();
	}
};
template <typename Kt, typename Vt>
string linked_list_to_str(Linked_list< Pair<Kt, Vt>* >* list) {
	string string_repr = "";

	Node< Pair<Kt, Vt>* >* current = list->Head;
	while (current) {
		string_repr += current->data->key + " -> " + std::to_string(current->data->value);

		if (current->next != nullptr) string_repr += ",";
		else string_repr += ";";

		current = current->next;
	}
	return string_repr;
}

string random_key(const int length)
{
	static constexpr char alphabet[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	string key;
	key.reserve(length);

	for (int i = 0; i < length; i++)
		key += alphabet[rand() % (sizeof(alphabet) - 1)];

	return key;
}


void print_execution_time(const clock_t t1, const clock_t t2)
{
	const double exec_time = (t2 - t1) / static_cast<double>(CLOCKS_PER_SEC);
	cout << "┏━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━┓\n" << setw(25) << left
		<< "┃Execution time" << "┃" << setw(19) << left << exec_time * 1000.0 << " ms┃\n";
}
void print_searching_time(const clock_t t1, const clock_t t2) {
	const double searching_time = (t2 - t1) / static_cast<double>(CLOCKS_PER_SEC);
	cout << "Searching time: " << searching_time << " ms\n";
}
int main()
{
	SetConsoleOutputCP(65001);
	srand(static_cast<unsigned>(time(nullptr)));

	constexpr int MAX_ORDER = 7;
	HashTable <string, int>* ht = new HashTable <string, int>();

	for (int o = 1; o <= MAX_ORDER; o++)
	{
		const int n = static_cast<int>(pow(10, o));

		clock_t t1 = clock();
		for (int i = 0; i < n; i++)
			ht->put(random_key(6), i); // dodawanie elementu
		clock_t t2 = clock();

		print_execution_time(t1, t2);
		cout << ht->to_string(linked_list_to_str) << endl;

		const int m = static_cast<int>(pow(10, 4));
		int hits = 0;

		t1 = clock();
		for (int i = 0; i < m; i++)
		{
			Pair<string, int>* entry = ht->get(random_key(6));
			if (entry != NULL)
				hits++;
		}
		t2 = clock();

		print_searching_time(t1, t2);
		ht->print_hits_count(hits);

		ht->print_stats();
		ht->clear();
	}
	delete ht;
	return 0;
}