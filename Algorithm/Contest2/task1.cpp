#include <iostream>
#include <cstddef>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int MOD = 1000000009;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;

vvi g;
vi values;
vb used;

void dfs(int v)
{
    used[v] = true;
    for (size_t i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (!used[to]) {
            dfs(to);
        }
    }
    
    int sum = values[v];
    int max_item = values[v];
    for (size_t i = 0; i < g[v].size(); ++i) {
        sum += values[g[v][i]];
        max_item = std::max(max_item, values[g[v][i]]);
    }
    values[v] = std::max(sum, max_item);
}

int main()
{
    // freopen("input.txt", "r", stdin);
    int n;
    cin >> n;

    g.assign(n, vi());
    used.assign(n, false);
    values.assign(n, 0);

    int t, v;
    cin >> t;
    values[0] = t;
    for (int i = 1; i < n; ++i) {
        cin >> t >> v;
        g[t - 1].push_back(i);
        values[i] = v;
    }

    // for (size_t i = 0; i < g.size(); ++i) {
//         cout << i << "(" << values[i] << "): ";
//         for (size_t j = 0; j < g[i].size(); ++j) {
//             cout << g[i][j] << " (" << values[g[i][j]] << ") ";
//         }
//         cout << endl;
//     }
// 
//     for (size_t i = 0; i < values.size(); ++i) {
//         cout << values[i] << " ";
//     }
//     cout << endl;
    
    dfs(0);
    cout << values[0] << endl;
    return 0;
}
