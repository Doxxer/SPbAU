#include "Vector.hpp"
#include <cstdio>
#include <cassert>

Vector::Vector() : size(0), capacity(2), data(new int[capacity])
{
	
}

Vector::Vector(size_t initialSize) : size(initialSize), capacity(size*2), data(new int[capacity])
{
	for(size_t i = 0; i < size; ++i)
	{
		data[i] = 0;
	}
}

Vector::Vector(Vector const& v)
{
	size = v.size;
	capacity = v.capacity;	
	data = new int[capacity];
	copy(v.data, data, size);
}

Vector::~Vector()
{
	delete[] data;
}

void Vector::print() const
{
	for(size_t i = 0; i < size; ++i)
	{
		printf("%d%c", data[i], i != size-1 ? ' ' : '\n');
	}
}

Vector& Vector::operator=(Vector& v)
{
	if (this != &v)
	{
		delete[] data;
		size = v.size;
		capacity = v.capacity;	
		data = new int[capacity];
		copy(v.data, data, size);
	}
	return *this;
}

void Vector::reserve(size_t newCapacity)
{
	if (capacity < newCapacity)
	{
		capacity = newCapacity;
		int* temp = new int[capacity];
		copy(data, temp, size);
		delete[] data;
		data = temp;
	}
}

void Vector::resize(size_t newSize)
{
	if (newSize > capacity)
		reserve(newSize*2);
	for (size_t i = size; i < newSize; ++i)
		data[i] = 0;
	size = newSize;
}

void Vector::add(int p)
{
	data[size++] = p;
	if (size == capacity)
		reserve(capacity*2);	
}

int& Vector::get(size_t i)
{
	assert(i < size);
	return data[i];
}

size_t Vector::get_size() const
{
	return size;
}

void Vector::copy(int* source, int* dest, size_t count)
{
	for(size_t i = 0; i < count; ++i)
	{
		dest[i] = source[i];
	}
}