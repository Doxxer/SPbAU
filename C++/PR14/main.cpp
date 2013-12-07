#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

bool less(void *a, void *b)
{
    return *((int *)a) < *((int *)b);
}

bool less_d(void *a, void *b)
{
    return *((double *)a) < *((double *)b);
}

void swap(void *const a, void *const b, size_t size)
{
    char *f1 = (char *)a;
    char *f2 = (char *)b;
    for (size_t i = 0; i < size; ++i) {
        std::swap(f1[i], f2[i]);
    }
}

// array, size of element, count of elements, cmp
void sort(void *const data, size_t size, size_t count, bool (*cmp)(void *, void *))
{
    char *const a = (char *)data;
    for (size_t i = 0; i < count; ++i) {
        for (size_t j = i + 1; j < count; ++j) {
            if (!cmp(a + size * i, a + size * j)) {
                swap(a + size * i, a + size * j, size);
            }
        }
    }
}

void test(size_t n)
{
    double *a = new double[n];
    for (size_t i = 0; i < n; ++i) {
        a[i] = (rand() % 500) / 3.0;
    }

    sort(a, sizeof(double), n, less_d);

    for (size_t i = 0; i < n; ++i)
        cout << a[i] << " ";
    cout << endl;
}

int main()
{
    size_t n = 100;
    srand(time(0));

    test(n);
    return 0;
}
