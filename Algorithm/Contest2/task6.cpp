#include <iostream>
#include <cstddef>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

const int MOD = 1000000009;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<string> vs;
typedef vector<vs> vvs;

string str(int k)
{
    stringstream ss;
    ss << k;
    return ss.str();
}

int main()
{
    // freopen("input.txt", "r", stdin);
    string s;
    cin >> s;
    int n = s.length();

    vvi dp(n + 1, vi(n + 1, 0));
    vvs dp_s(n + 1, vs(n + 1, ""));

    for (int len = 1; len <= n; ++len) {
        for (int l = 0; l + len <= n; ++l) {
            int r = l + len;

            dp[l][r] = len;
            dp_s[l][r] = s.substr(l, len);

            for (int i = l + 1; i < r; ++i) {
                if (dp[l][r] > dp[l][i] + dp[i][r]) {
                    dp[l][r] = dp[l][i] + dp[i][r];
                    dp_s[l][r] = dp_s[l][i] + dp_s[i][r];
                }
            }

            for (int cnt = 2; cnt <= len; ++cnt) {
                if (len % cnt == 0) {
                    bool good = 1;
                    string s1 = s.substr(l, len / cnt);
                    for (int i = 0; i < cnt; ++i) {
                        string s2 = s.substr(l + (len / cnt) * i, len / cnt);
                        good &= (s1 == s2);
                    }
                    if (good) {
                        if (dp[l][r] > str(cnt).length() + 1 + dp[l][l + len / cnt] + 1) {
                            dp[l][r] = str(cnt).length() + 1 + dp[l][l + len / cnt] + 1;
                            dp_s[l][r] = str(cnt) + "(" + dp_s[l][l + len / cnt] + ")";
                        }
                    }
                }
            }
        }
    }
    cout << dp[0][n] << endl << dp_s[0][n] << endl;
    return 0;
}
