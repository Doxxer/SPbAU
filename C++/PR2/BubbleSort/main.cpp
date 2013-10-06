#include <cstdio>
#include <cstdlib>
#include "sort.h"

void print(int* a, int n)
{
	for(size_t i = 0; i < n; ++i)
		printf("%d ", a[i]);
	printf("\n");
}

int main (int argc, char const *argv[])
{
	int n = 50;
	
	int* a = new int[n];

	for(size_t i = 0; i < n; ++i)
		a[i] = rand() % 100;
	 
	print(a, n);	
	sort(a, n);
	print(a, n);
		
	delete[] a;
	return 0;
}