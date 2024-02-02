#pragma once
#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Element
{
public:
	T value = NULL;
	Element *next{};
	Element *prev{};

	Element() = default;
	Element(T value)
	{
		this->value = value;
	}
	~Element()
	{
		delete value;
		value = nullptr;
	}
};

template <typename T>
class LinkedList
{
private:
	Element<T> *head{};
	Element<T> *tail{};
	size_t size{};

	void push_element(Element<T> *temp, T value)
	{
		Element<T> *element = new Element<T>();
		element->value = value;

		if (temp == tail)
			add_behind(value);

		element->next = temp->next;
		temp->next = element;
		element->prev = temp;
		element->next->prev = element;
	}

	void push_before_element(Element<T> *temp, T value)
	{
		Element<T> *element = new Element<T>();
		element->value = value;

		if (temp == head)
			add_ahead(value);

		element->prev = temp->prev;
		temp->prev = element;
		element->next = temp;
		element->prevoius->next = element;
	}

public:
	LinkedList() : head(nullptr), tail(nullptr), size(0) {}
	~LinkedList()
	{
		for (size_t i = 0; i < size; i++)
		{
			if (head == tail)
			{
				delete tail;
				head = nullptr;
				tail = nullptr;
				break;
			}
			else
			{
				tail = tail->prev;
				delete tail->next;
				tail->next = nullptr;
			}
		}
		size = 0;
	}

	T operator[](size_t ind)
	{
		if (ind > size)
			cout << "Index out of range" << endl;

		if (ind < ceil(size / 2))
		{
			Element<T> *buff = head;
			for (size_t i = 0; i < ind; i++)
				buff = buff->next;
			return buff->value;
		}
		else
		{
			Element<T> *buff = tail;
			size_t i_size = size - 1;
			for (size_t i = i_size; i > ind; i--)
				buff = buff->prev;
			return buff->value;
		}
	}

	void push_back(T value)
	{
		Element<T> *element = new Element<T>(value);

		if (size == 0)
		{
			head = element;
			tail = element;
		}
		else
		{
			tail->next = element;
			element->prev = tail;
			tail = element;
		}
		size++;
	}

	void push_front(T value)
	{
		Element<T> *element = new Element<T>(value);

		if (size == 0)
		{
			head = element;
			tail = element;
		}
		else
		{
			element->next = head;
			head->prev = element;
			head = element;
		}
		size++;
	}

	void pop_back()
	{
		if (size == 1)
		{
			delete tail;
			tail = nullptr;
			head = nullptr;
		}
		else
		{
			tail = tail->prev;
			delete tail->next;
			tail->next = nullptr;
		}
		size--;
	}

	void remove_ahead()
	{
		if (size == 1)
		{
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		else
		{
			head = head->next;
			delete head->prev;
			head->prev = nullptr;
		}
		size--;
	}

	void delete_all()
	{
		for (size_t i = 0; i < size; i++)
		{
			if (head == tail)
			{
				delete tail;
				head = nullptr;
				tail = nullptr;
				break;
			}
			else
			{
				tail = tail->prev;
				delete tail->next;
				tail->next = nullptr;
			}
		}
		size = 0;
	}

	void add_with_sorting(T value, int (*cmp)(T, T))
	{
		if (size > 0)
		{
			Element<T> *temp = head;
			int flag = 1;
			while (flag == 1)
			{
				int result = cmp(value, temp->value);
				if (result >= 0)
				{
					push_element(temp, value);
					flag = 0;
				}
				else if (result == -1)
				{
					push_before_element(temp, value);
					flag = 0;
				}
				temp = temp->next;
			}
		}
		else
			push_back(value);
	}
};