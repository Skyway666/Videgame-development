#ifndef DYNARRAY_H
#define DYNARRAY_H

#include <assert.h>
#include <iostream>


#define min(a, b) (a < b) ? a : b

#define MIN_ARRAY_BLOCK_SIZE 10

template <class T>
class DynArray {
public:
	DynArray();
	DynArray(unsigned int memSize);
	DynArray(DynArray &&other);
	~DynArray();

	bool empty() const;
	unsigned int size() const;

	bool insert(unsigned int index, const T& elem);
	bool remove(unsigned int index);


	T& operator[] (unsigned int index) const;
	void shrinkToFit();

	void print() const;	
	//List<T> list_converter();

private:
	void allocMem(unsigned int memSize);

	T* arrayElems;
	unsigned int memSize;
	unsigned int numElems;
};

template <class T>
DynArray<T>::DynArray() :
	arrayElems(NULL),
	memSize(MIN_ARRAY_BLOCK_SIZE),
	numElems(0)
{
	allocMem(memSize);
}

template <class T>
DynArray<T>::DynArray(unsigned int memorySize) :
	arrayElems(NULL),
	memSize(memorySize),
	numElems(0)
{
	allocMem(memSize);
}

template <class T>
DynArray<T>::DynArray(DynArray &&other) :
	arrayElems{ other.arrayElems },
	memSize{other.memSize},
	numElems{other.numElems}
{
	other.arrayElems = nullptr;
}

template <class T>
DynArray<T>::~DynArray()
{
	delete[] arrayElems;
}

template <class T>
bool DynArray<T>::empty() const
{
	return numElems == 0;
}

template <class T>
unsigned int DynArray<T>::size() const
{
	return numElems;
}

template <class T>
bool DynArray<T>::insert(unsigned int index, const T& elem)
{
	// Return false if the index is out of bounds
	if (index > numElems)
		return false;

	// If the array is full, reserve more memory
	if (numElems >= memSize)
	{
		allocMem(memSize + MIN_ARRAY_BLOCK_SIZE);
	}

	// Shift elements from index one position rightwards
	for (unsigned int i = numElems; i > index; --i)
	{
		arrayElems[i] = arrayElems[i - 1];
	}

	// Insert the element into the empty position
	arrayElems[index] = elem;
	numElems++;
	return true;
}

template <class T>
bool DynArray<T>::remove(unsigned int index)
{
	// Return false if the index is out of bounds
	if (index >= numElems)
		return false;

	// Shift elements at the right of index one position to the left
	// (the element at index gets overwritten/removed)
	for (unsigned int i = index; i < numElems - 1; ++i)
	{
		arrayElems[i] = arrayElems[i + 1];
	}

	numElems--;
	return true;
}

template <class T>
T& DynArray<T>::operator[] (unsigned int index) const
{
	assert(index < numElems && "operator[] out of bounds");
	return arrayElems[index];
}

template <class T>
void DynArray<T>::shrinkToFit()
{
	if (numElems < memSize)
		allocMem(numElems);
}

template <class T>
void DynArray<T>::print() const
{
	if (numElems == 0)
	{
		std::cout << "Dynamic array empty" << std::endl;
	}
	else
	{
		for (unsigned int i = 0; i < numElems; ++i)
			std::cout << arrayElems[i] << " ";

		std::cout << std::endl;
	}
}

template <class T>
void DynArray<T>::allocMem(unsigned int newMemSize)
{
	// Allocate memory for the new array
	T *newArrayElems = new T[newMemSize];

	// Calculate the new number of elements
	unsigned int newNumElems = min(numElems, newMemSize);

	// Copy the old array into the new one
	for (unsigned int i = 0; i < newNumElems; ++i)
		newArrayElems[i] = arrayElems[i];

	// Delete old array
	if (arrayElems != NULL)
		delete[] arrayElems;

	// Assign new values
	arrayElems = newArrayElems;
	memSize = newMemSize;
	numElems = newNumElems;
}

/*
template<class T>
List<T> DynArray<T>::list_converter() 
{
	List<T> newList = List<T>();


	for (int i = 0; i < numElems; i++)
	{
		newList.pushBack(this[i]);
	}

	newList.shrinkToFit();
	return newList;
} */

#endif

