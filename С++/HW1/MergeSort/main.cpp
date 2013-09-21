#include <cstdio>
#include "mergesort.h"

void print(int *a, size_t n)
{
	for(size_t i = 0; i < n; ++i)
		printf("%d%c", *(a+i), i == n-1 ? '\n' : ' ');
}

int main()
{
	freopen("input.txt", "r", stdin);
	size_t n;
	scanf("%zd\n", &n);
	int *a = new int[n], *buffer = new int[n];
	
	for(size_t i = 0; i < n; ++i)
		scanf("%d", a+i);
	
	print(a, n);
	sort(a, n, buffer);
	print(a, n);
	
	delete[] a;
	delete[] buffer;
	return 0;
}