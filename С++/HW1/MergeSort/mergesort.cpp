#include "mergesort.h"

void merge(int* a, int p, int q, int r, int* buffer)
{
	int n1 = q - p + 1;
    
	for (int i = 0; i < n1; i++)
		*(buffer + i) = *(a + p + i);
    
	int i = 0, j = q + 1, k = p;
    for (; i < n1 && j < r + 1; k++) {
        if (*(buffer + i) <= *(a + j)) {
            *(a+k) = *(buffer + i);
            i++;
        } else {
            *(a+k) = *(a+j);
			j++;			
        }
    }

    if (i < n1) {
        for (int t = i; t < n1; t++, k++) {
            *(a+k) = *(buffer + t);
        }
    } else
	{
        for (int t = j; t < r + 1; t++, k++) {
            *(a+k) = *(a+t);
		}
	}
}

void mergesort(int* a, int l, int r, int* buffer)
{
	if (l < r)
	{
		int q = (l+r)/2;
		mergesort(a, l, q, buffer);
		mergesort(a, q+1, r, buffer);
		merge(a, l, q, r, buffer);
	}
}

void sort(int *a, size_t n, int* buffer)
{
	mergesort(a, 0, n-1, buffer);
}
