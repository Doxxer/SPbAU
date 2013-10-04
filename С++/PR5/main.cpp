#include "Vector.hpp"
#include <cassert>

int main ()
{
	Vector v;
	assert(v.get_size() == 0);
	
	v.add(10);
	assert(v.get_size() == 1);
	
	v.add(20);
	assert(v.get_size() == 2);
	
	v.add(30);
	assert(v.get_size() == 3);
	
	v.add(40);
	assert(v.get_size() == 4);
	
	v.resize(10);
	v.print();
	
	v.add(5);
	v.add(5);
	v.add(5);
	assert(v.get_size() == 13);
	
	v.resize(2);
	assert(v.get_size() == 2);
	
	v.resize(13);
	v.print();	
	
	Vector p(v);
	p.print();
	
	p.get(3) = 333;
	assert(p.get(3) == 333);
	p.print();	
	
	return 0;
}