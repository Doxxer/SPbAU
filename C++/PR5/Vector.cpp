#include "Vector.hpp"
#include <cstdio>
#include <cassert>
#include <algorithm>

Vector::Vector(size_t initialSize, int value) :
	increase_factor(2.0),
	size(initialSize), 
	capacity(std::max(initialSize, 16ul)),
	data(new int[capacity])
{
	std::fill(data, data + size, value);
}

Vector::Vector(Vector const &other) :
	increase_factor(2.0),
	size(other.size), 
	capacity(other.capacity),
	data(new int[capacity])
{
	std::copy(other.data, other.data + size, data);
}

Vector::~Vector()
{
	delete[] data;
}

Vector& Vector::operator=(Vector const& other)
{
	if (this != &other)
		Vector(other).swap(*this);
	return *this;	
}

void Vector::add(int value)
{
	reserve(size + 1);
	data[size++] = value;	
}

void Vector::reserve(size_t newCapacity)
{
	if (newCapacity > capacity)
	{
		newCapacity = std::max(newCapacity, (size_t)(capacity * increase_factor));
		int *temp = new int[newCapacity];
		std::copy(data, data + size, temp);
		delete[] data;
		data = temp;
		capacity = newCapacity;
	}
}

void Vector::resize(size_t newSize)
{
    reserve(newSize);
    std::fill(data + size, data + newSize, 0u);
    size = newSize;
}

int& Vector::get(size_t i)
{
	return data[i];
}

int Vector::get(size_t i) const
{
	return data[i];
}

size_t Vector::get_size() const
{
	return size;
}

void Vector::swap(Vector &other)
{
	std::swap(size, other.size);
	std::swap(capacity, other.capacity);
	std::swap(data, other.data);
}
