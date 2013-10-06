#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>

class Vector
{
public:
	explicit Vector(size_t initialSize = 0u, int value = 0);
	explicit Vector(Vector const &other);	

	~Vector();
	
	Vector& operator=(Vector const &other);
	
	void add(int value);
	void reserve(size_t size);
	void resize(size_t size);
	
	int& get(size_t i);
	int get(size_t i) const;
	
	size_t get_size() const;
	void swap(Vector &other);
	
private:
	const float increase_factor;
	
	size_t size;
	size_t capacity;
	int* data;
};

#endif /* end of include guard: VECTOR_H */
