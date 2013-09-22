#include <cstdio>
#include <sys/stat.h>
#include "mergesort.h"

void print(int *a, size_t n)
{
	for(size_t i = 0; i < n; ++i)
		printf("%d%c", *(a+i), i == n-1 ? '\n' : ' ');
}

bool fileExists(const char* file)
{
	struct stat buf;
	return stat(file, &buf) == 0;
}

int main (int argc, char **argv)
{
	if (argc > 1 && fileExists(argv[1]))
		freopen(argv[1], "r", stdin);
	
	size_t n = 0;
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