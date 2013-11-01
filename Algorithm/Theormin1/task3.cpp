#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

#define X first
#define Y second
#define MP make_pair
#define PB push_back

typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vi> vvi;

vvi g;
vi topsort;
vi color;

bool dfs(int v)
{
    color[v] = 1;
    for (vi::iterator it = g[v].begin(); it != g[v].end(); ++it) {
        if (color[*it] == 0) {
            if (dfs(*it))
                return true;
        } else if (color[*it] == 1) {
            return true;
        }
    }
    color[v] = 2;
    topsort.PB(v);
    return false;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    int n, m, v1, v2;
    scanf("%d%d", &n, &m);
    g.assign(n, vi(0));
    color.assign(n, 0);

    for (int i = 0; i < m; ++i) {
        scanf("%d%d", &v1, &v2);
        v1--, v2--;
        g[v1].PB(v2);
    }
    for (int i = 0; i < n; ++i) {
        if (color[i] == 0)
            if (dfs(i)) {
                return cout << "-1" << endl, 0;
            }
    }
    for (int i = n - 1; i >= 0; --i)
        printf("%d ", topsort[i] + 1);
    printf("\n");
    return 0;
}
