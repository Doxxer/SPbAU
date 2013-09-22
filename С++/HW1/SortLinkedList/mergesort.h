#ifndef MERGESORT_H
#define MERGESORT_H

struct Node
{
	int value;
	Node* next;
	
	Node(int v, Node* next = 0) : value(v), next(next)
	{
	}
};

Node* add(Node* list, int value);
Node* sort(Node* list);

void print(Node* list);
void clear(Node* list);

#endif /* end of include guard: MERGESORT_H */