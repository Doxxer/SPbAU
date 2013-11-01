#include <iostream>
#include <cstdio>
#include <vector>
#include <set>

using namespace std;

#define X first
#define Y second
#define MP make_pair
#define PB push_back

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef set<ii> sii;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vi> vvi;

vvi g, gt;
vi topsort1, comp;
vb used;

void dfs1(int v)
{
    used[v] = true;
    for (vi::iterator it = g[v].begin(); it != g[v].end(); ++it) {
        if (!used[*it])
            dfs1(*it);
    }
    topsort1.PB(v);
}

void dfs2(int v)
{
    used[v] = true;
    comp.PB(v);
    for (vi::iterator it = gt[v].begin(); it != gt[v].end(); ++it) {
        if (!used[*it])
            dfs2(*it);
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    int n, m, v1, v2, c = 0;
    scanf("%d%d", &n, &m);

    g.assign(n, vi(0));
    gt.assign(n, vi(0));
    used.assign(n, false);
    vi scc(n, 0);

    vii e;
    for (int i = 0; i < m; ++i) {
        scanf("%d%d", &v1, &v2);
        v1--, v2--;
        g[v1].PB(v2);
        gt[v2].PB(v1);
        e.PB(MP(v1, v2));
    }

    used.assign(n, false);
    for (int i = 0; i < n; ++i)
        if (!used[i])
            dfs1(i);

    used.assign(n, false);
    for (int i = 0; i < n; ++i) {
        int v = topsort1[n - 1 - i];
        if (!used[v]) {
            dfs2(v);
            for (size_t j = 0; j < comp.size(); ++j)
                scc[comp[j]] = c;
            c++;
            comp.clear();
        }
    }

    sii edges;
    for (int i = 0; i < m; ++i) {
        if (scc[e[i].X] != scc[e[i].Y]) {
            edges.insert(MP(scc[e[i].X], scc[e[i].Y]));
        }
    }
    cout << edges.size() << endl;
    return 0;
}
