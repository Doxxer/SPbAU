#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
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
map<ii, int> edges;
set<int> res;

void dfs(int v, int par = -1)
{
    used[v] = true;
    tin[v] = fup[v] = timer++;
    for (size_t i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (to == par)
            continue;
        if (used[to])
            fup[v] = min(fup[v], tin[to]);
        else {
            dfs(to, v);
            fup[v] = min(fup[v], fup[to]);
            if (fup[to] > tin[v])
                res.insert(edges[MP(v, to)]);
        }
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);

    int n, m, a, b;
    scanf("%d %d", &n, &m);
    g.resize(n, vi());
    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &a, &b);
        --a, --b;
        g[a].PB(b);
        g[b].PB(a);
        edges[MP(a, b)] = edges[MP(b, a)] = i + 1;
    }

    timer = 0;
    used.assign(n, false);
    tin.assign(n, 0);
    fup.assign(n, 0);
    for (int i = 0; i < n; ++i)
        if (!used[i])
            dfs(i);
    printf("%ld\n", res.size());
    for(set<int>::iterator it=res.begin();it!=res.end();++it)
        printf("%d ", *it);
    printf("\n");
    return 0;
}
