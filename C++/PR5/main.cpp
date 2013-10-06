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
	
	Vector z(15);
	assert(z.get_size() == 15);
	
	return 0;
}
