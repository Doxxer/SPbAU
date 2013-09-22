#include <cstdio>
#include "mergesort.h"

int main()
{	
	freopen("input.txt", "r", stdin);
	size_t n;
	scanf("%zd\n", &n);
		
	Node* list(0);
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