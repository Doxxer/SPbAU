#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

#define X first
#define Y second
#define MP make_pair
#define PB push_back

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef pair<int, int> ii;

vvi g;
vb used;
vi tin, fup;
int timer;
set<int> res;

void dfs(int v, int par = -1)
{
    used[v] = true;
    tin[v] = fup[v] = timer++;
    int children = 0;
    for (size_t i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (to == par)
            continue;
        if (used[to])
            fup[v] = min(fup[v], tin[to]);
        else {
            dfs(to, v);
            fup[v] = min(fup[v], fup[to]);
            if (fup[to] >= tin[v] && par != -1)
                res.insert(v);
            ++children;
        }
    }
    if (par == -1 && children > 1)
        res.insert(v);
}

int main()
{
    // freopen("input.txt", "r", stdin);

    int n, m, a, b;
    scanf("%d %d", &n, &m);
    g.assign(n, vi());
    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &a, &b);
        --a, --b;
        g[a].PB(b);
        g[b].PB(a);
    }

    timer = 0;
    used.assign(n, false);
    tin.assign(n, 0);
    fup.assign(n, 0);

    for (int i = 0; i < n; ++i)
        if (!used[i])
            dfs(i);
    printf("%ld\n", res.size());
    for (set<int>::iterator it = res.begin(); it != res.end(); ++it)
        printf("%d ", *it + 1);
    printf("\n");
    return 0;
}
