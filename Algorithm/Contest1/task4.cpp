#include <iostream>
#include <cstddef>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;

#define X first
#define Y second
#define MP make_pair

pll process(vll const &v)
{
    vll sl(v.size(), 0);
    vll sr(v.size(), 0);
    ll lsum = 0, rsum = 0;

    for (size_t i = 1; i < v.size(); ++i) {
        rsum += v[v.size() - i];
        lsum += v[i - 1];
        sl[i] = sl[i - 1] + lsum;
        sr[v.size() - 1 - i] = sr[v.size() - i] + rsum;
    }
    ll min = sl[0] + sr[0], index = 0;
    for (size_t i = 0; i < v.size(); ++i) {
        ll t = sl[i] + sr[i];
        if (t < min) {
            min = t;
            index = i;
        }
    }
    return MP(min, index);
}

int main()
{
    int m, n;
    vll h, w;
    ll sum = 0;

    // freopen("input.txt", "r", stdin);
    cin >> m >> n;
    int t;
    h.assign(n, 0);
    w.assign(m, 0);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &t);
            t *= 2;
            h[j] += t;
            w[i] += t;
            sum += t;
        }
    }
    pll hmin = process(h);
    pll wmin = process(w);
    cout << wmin.Y + 1 << " " << hmin.Y + 1 << endl << wmin.X + hmin.X + sum << endl;
    return 0;
}
