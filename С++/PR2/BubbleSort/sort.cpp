#include <algorithm>

void sort(int* a, int size)
{
	bool f = true;
	while(f)
	{
		f = false;
		for(int i = 0; i < size-1; ++i)
		{
			if(a[i] > a[i+1])
			{	
				std::swap(a[i], a[i+1]);
				f = true;
			}
		}
	}
}