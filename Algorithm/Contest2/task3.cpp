#include <iostream>
#include <cstddef>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int MOD = 1000000009;

typedef vector<int> vi;
typedef vector<vi> vvi;

int main()
{
    // freopen("input.txt", "r", stdin);
    int n, A;
    cin >> n >> A;
    vi a(n, 0);
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    vvi dp(A + 1, vi(n + 1, 0));
    std::fill(dp[0].begin(), dp[0].end(), 1);
    
    for (int i = 1; i <= A; ++i) {
        for (int j = 1; j <= n; ++j) {
            dp[i][j] = ((i - a[j - 1] >= 0 ? dp[i - a[j - 1]][j] : 0) + dp[i][j - 1]) % MOD;
        }
    }
    cout << dp[A][n] << endl;
    return 0;
}
