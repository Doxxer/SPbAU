#ifndef VECTOR_H
#define VECTOR_H

#include <cstdio>

class Vector
{
public:
	Vector();
	~Vector();
	explicit Vector(Vector const& v);
	explicit Vector(size_t initialSize);
	Vector& operator=(Vector& v);
	
	void add(int p);
	int& get(size_t i);
	void reserve(size_t);
	void resize(size_t size);
	size_t get_size() const;
	void print() const;

private:
	size_t size; // real data size
	size_t capacity; // whole size
	int* data;
	
	void copy(int* source, int* desc, size_t count);
};

#endif /* end of include guard: VECTOR_H */
