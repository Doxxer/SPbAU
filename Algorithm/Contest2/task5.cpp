#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <string>
#include <set>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

const int MOD = 1000000009;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<string> vs;
typedef map<int, ll> mii;
typedef vector<vector<mii> > dyn;

dyn d;
int n, m;

struct Mask {
    vi mask;
    vi link;
    int dec_value;
    bool ok;

    Mask() : dec_value(-1), ok(false)
    {
    }

    Mask(int value) : dec_value(value), ok(false)
    {
        mask.assign(n + 1, 0);
        link.assign(n + 1, 0);

        int a = 0, b = 0;
        for (int i = n; i >= 0 && value; --i) {
            mask[i] = value % 3;
            if (mask[i] == 1)
                ++a;
            else if (mask[i] == 2)
                ++b;
            value /= 3;
        }
        ok = (a == b);
        if (ok) {
            vi stack;
            for (int i = 0; i < n + 1; ++i) {
                if (mask[i] == 1)
                    stack.push_back(i);
                else if (mask[i] == 2) {
                    if (stack.empty()) {
                        ok = false;
                        break;
                    } else {
                        int p = stack.back();
                        stack.pop_back();
                        link[p] = i;
                        link[i] = p;
                    }
                }
            }
        }
    }
};

map<int, Mask> maskMap;

void fillmap()
{
    int max = 1;
    for (int i = 0; i < n + 1; ++i) {
        max *= 3;
    }
    for (int v = 0; v < max; ++v) {
        Mask t(v);
        if (t.ok)
            maskMap[v] = t;
    }
}

int three_to_dec(vi const &a)
{
    int res = 0;
    int st = 1;
    for (int i = (int)a.size() - 1; i >= 0; --i) {
        res += st * a[i];
        st *= 3;
    }
    return res;
}

vi where_can_we_go(int i, int k, int mask)
{
    vi res;
    vi tbin = maskMap[mask].mask;

    int core = 10 * tbin[k] + tbin[k + 1];
    int tbinkprev = tbin[k];
    int tbink1prev = tbin[k + 1];
    switch (core) {
        case 0:
            if (k < n - 1 && i < m - 1) {
                tbin[k] = 1;
                tbin[k + 1] = 2;
                res.push_back(three_to_dec(tbin));
            }
            break;
        case 10:
        case 20:
        case 1:
        case 2:
            if (k < n - 1) { // down
                tbin[k] = 0;
                if (core == 20 || core == 2)
                    tbin[k + 1] = 2;
                else
                    tbin[k + 1] = 1;
                res.push_back(three_to_dec(tbin));
                tbin[k] = tbinkprev;
                tbin[k + 1] = tbink1prev;
            }
            if (i < m - 1) { // right
                if (core == 20 || core == 2)
                    tbin[k] = 2;
                else
                    tbin[k] = 1;
                tbin[k + 1] = 0;
                res.push_back(three_to_dec(tbin));
            }
            break;
        case 12:
            if (i == m - 1 && k == n - 1) {
                tbin[k] = tbin[k + 1] = 0;
                res.push_back(three_to_dec(tbin));
            }
            break;
        case 11:
        case 22:
        case 21:
            vi link = maskMap[mask].link;
            // printf("pfff - %d %d. Core = %d, Mask = ", i, k, core);
            // for (size_t j = 0; j < tbin.size(); ++j) {
            //     printf("%d", tbin[j]);
            // }
            // printf(". Link = ");
            // for (size_t j = 0; j < link.size(); ++j) {
            //     printf("%d", link[j]);
            // }
            // printf("\n");

            tbin[k] = tbin[k + 1] = 0;
            int left = link[k + 1], right = link[k];
            if (left > right)
                swap(left, right);
            tbin[left] = 1;
            tbin[right] = 2;
            res.push_back(three_to_dec(tbin));
            break;
    }

    return res;
}

int main()
{
    freopen("input.txt", "r", stdin);

    cin >> n >> m;
    if (n > m)
        swap(n, m);
    d.assign(n + 1, vector<mii>(m));

    fillmap();

    // for (auto i = maskMap.begin(); i != maskMap.end(); i++) {
    //     vi mask = (i->second).mask;
    //     vi link = (i->second).link;
    //     printf("%d: ", i->second.dec_value);
    //     for (size_t i = 0; i < mask.size(); ++i) {
    //         printf("%d", mask[i]);
    //     }
    //     printf("; ");
    //     for (size_t i = 0; i < link.size(); ++i) {
    //         printf("%d", link[i]);
    //     }
    //     printf("\n");
    // }

    d[0][0][0] = 1;

    for (int i = 0; i < m; ++i) {
        for (int k = 0; k < n; ++k) {
            for (mii::iterator it = d[k][i].begin(); it != d[k][i].end(); ++it) {
                int mask = it->first;

                vi targets = where_can_we_go(i, k, mask);
                for (size_t j = 0; j < targets.size(); ++j) {
                    int mask_to = targets[j];
                    d[k + 1][i][mask_to] += d[k][i][mask];
                }
            }
            if (k == n - 1 && i < m - 1) {
                for (mii::iterator it = d[k + 1][i].begin(); it != d[k + 1][i].end(); ++it) {
                    d[0][i + 1][it->first / 3] = it->second;
                }
            }
        }
    }
    cout << d[n][m - 1][0] << endl;

    return 0;
}
