#include <cstdio>
#include <sys/stat.h>
#include "mergesort.h"

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
	scanf("%zd", &n);
		
	Node* list = 0;
	int temp;
	for(size_t i = 0; i < n; ++i)
	{
		scanf("%d", &temp);
		list = add(list, temp);
	}

	print(list);
	list = sort(list);
	print(list);
	
	clear(list);
	
	return 0;
}