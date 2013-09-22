#include "mergesort.h"
#include <cstdio>

// Add element with key = value to the head of list
Node* add(Node* list, int value)
{
	// he-he
	return list ? new Node(value, list) : new Node(value);
}

void print(Node* list)
{
	while(list)
	{
		printf("%d ", list->value);
		list = list->next;
	}
	printf("\n");
}

int length(Node* list)
{
	int res = 0;
	while(list)
	{
		list = list->next;
		res++;
	}
	return res;
}

Node* merge(Node* left, Node* mid)
{
	Node* newLeft = 0;
	Node* newRight = 0;

	if (left->value < mid->value) {
		newLeft = left;
		left = left->next;
	} else {
		newLeft = mid;
		mid = mid->next;
	}
	
	newRight = newLeft;
	while (left && mid) {
		if (left->value < mid->value) {
			newRight->next = left;
			left = left->next;
		} else {
			newRight->next = mid;
			mid = mid->next;
		}
		newRight = newRight->next;
	}
	
	if (left)
			newRight->next = left;
	if (mid)
			newRight->next = mid;
	
	return newLeft;
}

Node* sort(Node* list)
{
	if (list->next == NULL)
		return list;
	
	Node* mid = list;
	int len = length(list);
	for(int i = 0; i < (len-1)/2; ++i)
		mid = mid->next;
	
	Node* afterMid = mid->next;
	mid->next = 0;
	
	return merge(sort(list), sort(afterMid));
}

void clear(Node* list)
{
	while(list)
	{
		Node* tmp = list->next;
		delete list;
		list = tmp;
	}
}