#include <iostream>
#include <cstddef>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;

const int MOD = 1000000009;

typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<string> vs;

int n;
string s;

vvi L;
vi parent;

// L[i] - начала всех палиндромов, заканчивающихся на s[i]
void count_L()
{
    int left, right;
    for (int i = 0; i < n; ++i) {
        left = right = i;
        while (left >= 0 && right < n && s[left] == s[right]) {
            L[right].push_back(left);
            --left;
            ++right;
        }

        left = i;
        right = i + 1;
        while (left >= 0 && right < n && s[left] == s[right]) {
            L[right].push_back(left);
            --left;
            ++right;
        }
    }
}

int solve()
{
    // dynamic. dp[i] = count of palin in the s[:i] (lenght = i). global answer = dp[n]
    vi dp(n + 1, 0);

    for (int i = 0; i < n; ++i) {
        int min = INT_MAX;
        int prev = 0;
        for (size_t j = 0; j < L[i].size(); ++j) {
            if (min > dp[L[i][j]] + 1) {
                min = dp[L[i][j]] + 1;
                prev = L[i][j];
            }
        }
        dp[i + 1] = min;
        parent[i + 1] = prev;
    }
    return dp[n];
}

int main()
{
    // freopen("input.txt", "r", stdin);
    cin >> n >> s;
    int ans_count = INT_MAX, ans_cycle = 0;
    string ans_s;
    vi ans_parent;

    for (int i = 0; i < n; ++i) {
        s = s.substr(1) + s[0];
        L.assign(n, vi());
        parent.assign(n + 1, 0);
        count_L();
        int temp_ans = solve();
        if (temp_ans < ans_count) {
            ans_count = temp_ans;
            ans_parent = vi(parent);
            ans_cycle = i + 1;
            ans_s = s;
        }
    }

    // print answer
    cout << ans_cycle << " " << ans_count << endl;
    vs strings;
    int end = n;
    do {
        strings.push_back(ans_s.substr(ans_parent[end], end - ans_parent[end]));
        end = ans_parent[end];
    } while (end);
    reverse(strings.begin(), strings.end());
    for (size_t i = 0; i < strings.size(); ++i) {
        cout << strings[i] << " ";
    }
    cout << endl;
    return 0;
}
