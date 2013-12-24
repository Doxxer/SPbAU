#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>

using namespace std;

typedef pair<int, int> ii;
typedef set<ii> sii;

bool cmp(ii a, ii b)
{
    double d1 = a.second * sqrt(2.0) + a.first;
    double d2 = b.second * sqrt(2.0) + b.first;
    return (d1 < d2);
}

ii dp[2][1001];

int main()
{
    //freopen("input.txt", "r", stdin);
    int n, m, k;
    cin >> n >> m >> k;

    sii s;

    for (int i = 0, r, c; i < k; ++i) {
        cin >> c >> r;
        s.insert(make_pair(r, c));
    }

    for (int c = 0; c <= n; ++c)
        dp[0][c] = make_pair(c, 0);

    for (int r = 1; r <= m; ++r) {
        dp[r & 1][0] = make_pair(r, 0);

        for (int c = 1; c <= n; ++c) {
            ii left = dp[(r & 1) ^ 1][c];
            left.first += 1;
            ii right = dp[(r & 1)][c - 1];
            right.first += 1;
            dp[r & 1][c] = min(left, right, cmp);

            if (s.find(make_pair(r, c)) != s.end()) {
                ii cross = dp[(r & 1) ^ 1][c - 1];
                cross.second += 1;
                dp[r & 1][c] = min(dp[r & 1][c], cross, cmp);
            }
        }
    }

    // cout << dp[m & 1][n].first << " " << dp[m & 1][n].second << endl;

    double res = dp[m & 1][n].first + dp[m & 1][n].second * sqrt(2.0);
    cout << round(100 * res) << endl;
    return 0;
}
