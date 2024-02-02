#pragma once
#include <iostream>
#include <sstream>

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
struct Linked_list {
public:
	Node<T>* Head{};
	Node<T>* Tail{};
	size_t size{};

	~Linked_list() {
		clear();
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
			Node<T>* buffer = Tail;
			size_t i_size = size - 1;
			for (size_t i = i_size; i > index; i--) buffer = buffer->previous;
			return buffer->data;
		}
		throw out_of_range("Out of range.");
	}

	void clear() {
		while (size > 0)
			remove_behind();
	}
};