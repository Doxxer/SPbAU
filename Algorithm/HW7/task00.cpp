#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;

vvi g;
vi group;
vb used;

void dfs(int v, int gr)
{
    used[v] = 1;
    group[v] = gr;
    for (size_t i = 0; i < g[v].size(); ++i) {
        if (!used[g[v][i]])
            dfs(g[v][i], !gr);
    }

    int c = 0;
    for (size_t j = 0; j < g[v].size(); ++j)
        if (group[g[v][j]] == group[v]) c++;

    if (c > 1) group[v] ^= 1;
}

int main()
{
    freopen("input.txt", "r", stdin);

    int n, t;
    cin >> n;
    g.assign(n, vi(0));

    // read graph
    for (int i = 0; i < n; ++i) {
        scanf("%d", &t);
        g[i].assign(t, 0);
        for (int j = 0; j < t; ++j) {
            scanf("%d", &g[i][j]);
            g[i][j]--;
        }
    }

    // partitioning    
    group.assign(n, 0);
    used.assign(n, false);
    for (int i = 0; i < n; ++i) {
        if (!used[i])
            dfs(i, 0);
    }
    
    // output
    int count = 0, gr = 0;
    for (int i = 0; i < n; ++i)
        if (group[i] == 0) count++;

    if (count > n - count) gr = 1, count = n - count;
    if (count == n - count) gr = group[0];

    printf("%d\n", count);

    for (int i = 0; i < n; ++i) {
        if (group[i] == gr) {
            printf("%d ", i + 1);
        }
    }
    printf("\n");    
    return 0;
}
