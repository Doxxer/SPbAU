#include "mergesort.h"

void copyArray(int* source, size_t sourceStartIndex, int* dest, size_t destStartIndex, size_t count)
{
	for (size_t i = 0; i < count; i++)
		*(dest + destStartIndex + i) = *(source + sourceStartIndex + i);
}

void merge(int* a, size_t p, size_t q, size_t r, int* buffer)
{
	size_t n1 = q - p + 1;
	
	copyArray(a, p, buffer, 0, n1);
	
	size_t i = 0, j = q + 1, k = p;
	for (; i < n1 && j < r + 1; k++) {
		if (*(buffer + i) <= *(a + j)) {
			*(a+k) = *(buffer + i);
			i++;
		} else {
			*(a+k) = *(a+j);
			j++;			
		}
	}

	if (i < n1)
		copyArray(buffer, i, a, k, n1 - i);
	else
		copyArray(a, j, a, k, r + 1 - j);
}

void mergesort(int* a, size_t l, size_t r, int* buffer)
{
	if (l < r)
	{
		size_t q = (l+r)/2;
		mergesort(a, l, q, buffer);
		mergesort(a, q+1, r, buffer);
		merge(a, l, q, r, buffer);
	}
}

void sort(int *a, size_t n, int* buffer)
{
	mergesort(a, 0, n-1, buffer);
}
