#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef vector<int> vi;

int main()
{
    // freopen("input.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    vi a(n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i]);

    vi d(n + 1, INFINITY), p(n + 1), idx(n + 1, -1);
    d[0] = -1;
    int length = 0;
    for (int i = 0; i < n; ++i) {
        int j = int(upper_bound(d.begin(), d.end(), a[i]) - d.begin());
        p[i] = idx[j - 1];
        if (d[j - 1] < a[i] && a[i] < d[j]) {
            d[j] = a[i];
            idx[j] = i;
            length = max(length, j);
        }
    }

    printf("%d\n", length);
    vi path;
    int pos = idx[length];
    while (pos != -1) {
    	path.push_back(pos);
    	pos = p[pos];
    }
    reverse (path.begin(), path.end());
    for (int i=0; i<(int)path.size(); ++i)
    	printf("%d ", a[path[i]]);
    printf("\n");
    return 0;
}
