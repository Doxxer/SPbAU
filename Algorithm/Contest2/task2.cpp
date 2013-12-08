#include <iostream>
#include <cstddef>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int MOD = 1000000009;

typedef vector<int> vi;
typedef vector<vi> vvi;

int n, m;
int max_mask;
vvi can;

bool check(int a, int b)
{
    for (int i = n - 1; i >= 0; --i) {
        bool p1 = (a & (1 << i)) != 0;
        bool p2 = (b & (1 << i)) != 0;

        if (p1 == 1 && p2 == 1)
            return false;
        if (p1 == 0 && p2 == 0) {
            if (i == 0)
                return false;
            bool p1next = (a & (1 << (i - 1))) != 0;
            bool p2next = (b & (1 << (i - 1))) != 0;
            if (p1next || p2next)
                return false;
            --i;
        }
    }
    return true;
}

void precalc_can()
{
    for (size_t i = 0; i < can.size(); ++i) {
        for (size_t j = 0; j < can[i].size(); ++j) {
            can[i][j] = check(i, j);
        }
    }
}

int main()
{
    //freopen("input.txt", "r", stdin);
    cin >> n >> m;

    max_mask = 1 << n;
    can.assign(max_mask, vi(max_mask, 0));
    precalc_can();
    
    vvi dp(m + 1, vi(max_mask, 0));
    dp[0][0] = 1;
    for(int pos = 1; pos <= m; ++pos)
    {
        for(int mask = 0; mask < max_mask; ++mask)
        {
            for(int next_mask = 0; next_mask < max_mask; ++next_mask)
            {
                dp[pos][mask] = (dp[pos][mask] + dp[pos - 1][next_mask] * can[mask][next_mask]) % MOD;
            }            
        }       
    }
    
    cout << dp[m][0] << endl;
    
    return 0;
}
