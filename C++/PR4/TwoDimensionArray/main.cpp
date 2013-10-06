#include <cstdio>

int main (int argc, char **argv)
{
	size_t N = 32512;
	
	if (argv[1][0] == '0')
	{
		int **p = new int*[N];
		for(size_t i = 0; i < N; ++i)
		{
			p[i] = new int[N];
		}
	}
	else
	{
		int **p = new int*[N];
		p[0] = new int[N*N];
		for(size_t i = 1; i < N; ++i)
		{
			p[i] = p[i-1] + N;
		}
	}
	return 0;
}