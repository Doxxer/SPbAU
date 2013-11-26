#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int> vi;

int main()
{
    freopen("input.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    vi a(n, 1);
    int swaps = 0;
    for (int i = 1; i < n; ++i) {
        a[i - 1] = i + 1;
        
        // pull up
        int j = i - 1;
        while (j) {
            int k = (j - 1) / 2;
            std::swap(a[j], a[k]);
            j = k;
            ++swaps;
        }
    }
    printf("%d\n", swaps);
    for (int i = 0; i < n; ++i) {
        printf("%d%c", a[i], i == n - 1 ? '\n' : ' ');
    }

    return 0;
}
