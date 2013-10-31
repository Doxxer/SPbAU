#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

typedef vector<int> vi;

int main()
{
    // freopen("input.txt", "r", stdin);
    int n;
    string s;
    cin >> n >> s;

    vi a(10);
    for (int i = 0; i < n; ++i)
        a[s[i] - 48]++;

    for (int i = 1; i < a.size(); ++i) {
        if (a[i]) {
            printf("%d", i);
            a[i]--;
            break;
        }
    }
    for (int i = 0; i < a.size(); ++i) {
        if (a[i]) {
            for (int j = 0; j < a[i]; ++j)
                printf("%d", i);
        }
    }
    printf("\n");
    return 0;
}
