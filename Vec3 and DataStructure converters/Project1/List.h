#ifndef LIST_H
#define LIST_H

#include <iostream> // std::cout and std::endl
#include <cassert> // assert

/**
* Double linked list.
*/
template <class T>
class List
{
public:

	List();

	~List();

	void pushFront(const T& elem);
	void pushBack(const T& elem);
	void popFront();
	void popBack();
	void insert(unsigned int pos, const T& elem);
	void remove(unsigned int pos);
	DynArray<T> dyn_array_converter() const;

	T front() const;
	T back() const;

	T getValue(unsigned int pos) const;

	bool empty() const;
	unsigned int size() const;
	void clear();

	void print() const;
	void printReverse() const;

private:

	struct node {
		T value;
		node *prev; // pointer to previous node
		node *next; // pointer to next node
	};

	node *first; // pointer to the first node
	node *last; // pointer to the last node
	unsigned int numElems; // number of elements in the list
};

template<class T>
List<T>::List() : first(nullptr), last(nullptr), numElems(0)
{
}

template<class T>
List<T>::~List()
{
	
	clear();
	
}

template<class T>
void List<T>::pushFront(const T& elem)
{
	node *aux = new node;
	aux->value = elem;
	aux->prev = nullptr;
	aux->next = first;
	first = aux;

	if (first->next)
	{
		first->next->prev = first;
	}

	if (numElems == 0) { last = aux; }
	numElems++;
}

template<class T>
void List<T>::pushBack(const T& elem)
{
	node *aux = new node;
	aux->value = elem;
	aux->prev = last;
	aux->next = nullptr;
	last = aux;

	if (last->prev)
	{
		last->prev->next = last;
	}

	if (numElems == 0) { first = aux; }
	numElems++;
}

template<class T>
void List<T>::popFront()
{
	// Abort if the list is empty
	assert(first != nullptr && "popFront() cannot be called if the list is empty");

	node *aux = first;
	first = first->next;
	if (first != nullptr) { first->prev = nullptr; }
	else { last = nullptr; }
	delete aux;
	numElems--;
}

template<class T>
void List<T>::popBack()
{
	// Abort if the list is empty
	assert(last != nullptr && "popBack() cannot be called if the list is empty");

	node *aux = last;
	last = last->prev;
	if (last != nullptr) { last->next = nullptr; }
	else { first = nullptr; }
	delete aux;
	numElems--;
}

template<class T>
void List<T>::insert(unsigned int pos, const T& elem)
{
	if (pos == 0)
	{
		pushFront(elem);
	}
	else if (pos == numElems) // position after the last node
	{
		pushBack(elem);
	}
	else
	{
		// Abort if the position is out of the bounds of the list
		assert(pos < numElems && "insert() needs a position within the bounds of the list");

		unsigned int count = 0;
		node *iterator = first;
		while (count < pos)
		{
			iterator = iterator->next;
			count++;
		}

		node *aux = new node;
		aux->value = elem;
		aux->prev = iterator->prev;
		aux->next = iterator;

		aux->prev->next = aux;
		aux->next->prev = aux;

		numElems++;
	}
}

template<class T>
void List<T>::remove(unsigned int pos)
{
	if (pos == 0)
	{
		popFront();
	}
	else if (pos == numElems - 1)
	{
		popBack();
	}
	else
	{
		// Abort if the position is out of the bounds of the list
		assert(pos < numElems && "remove() needs a position within the bounds of the list");

		unsigned int count = 0;
		node *iterator = first;
		while (count < pos)
		{
			iterator = iterator->next;
			count++;
		}

		iterator->prev->next = iterator->next;
		iterator->next->prev = iterator->prev;
		delete iterator;

		numElems--;
	}
}

template<class T>
T List<T>::front() const
{
	// Abort if the list is empty
	assert(first != nullptr && "The list is empty");

	return first->value;
}

template<class T>
T List<T>::back() const
{
	// Abort if the list is empty
	assert(first != nullptr && "The list is empty");

	return last->value;
}

template<class T>
T List<T>::getValue(unsigned int pos) const
{
	// Abort if the list is empty
	assert(pos < numElems && "Position out of bounds");

	unsigned int count = 0;
	node *iterator = first;
	while (count < pos && iterator->next != nullptr)
	{
		iterator = iterator->next;
		count++;
	}

	return iterator->value;
}

template<class T>
bool List<T>::empty() const
{
	return numElems == 0;
}

template<class T>
unsigned int List<T>::size() const
{
	return numElems;
}

template<class T>
void List<T>::clear()
{
	node *iterator = first;
	while (iterator != nullptr)
	{
		node *aux = iterator;
		iterator = iterator->next;
		delete aux;
	}
	first = nullptr;
	last = nullptr;
	numElems = 0;
}

template<class T>
void List<T>::print() const
{
	node *iterator = first;

	if (iterator == nullptr)
	{
		std::cout << "The list is empty";
	}
	else
	{
		std::cout << iterator->value;
		iterator = iterator->next;
	}

	while (iterator != nullptr)
	{
		std::cout << " <-> " << iterator->value;
		iterator = iterator->next;
	}

	std::cout << std::endl;
}

template<class T>
void List<T>::printReverse() const
{
	node *iterator = last;

	if (iterator == nullptr)
	{
		std::cout << "The list is empty";
	}
	else
	{
		std::cout << iterator->value;
		iterator = iterator->prev;
	}

	while (iterator != nullptr)
	{
		std::cout << " <-> " << iterator->value;
		iterator = iterator->prev;
	}

	std::cout << std::endl;
}

template<class T>
DynArray<T> List<T>::dyn_array_converter() const
{
	DynArray<T> newArray = DynArray<T>();

	
	for (int i = 0; i < numElems; i++)
	{
		newArray.insert(i, getValue(i));
	}

	newArray.shrinkToFit();
	return newArray;
}

#endif  //LIST_H


