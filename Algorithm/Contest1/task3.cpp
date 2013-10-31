#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

typedef vector<char> vc;

int main()
{
    // freopen("input.txt", "r", stdin);
    string s;
    int k = 0;
    cin >> s >> k;
    int n = (int)s.length();
    vc stack;
    int i = 0;

    for (; i < n && k; ++i) {
        while (!stack.empty() && stack.back() < s[i] && k) {
            w stack.pop_back();
            k--;
        }
        stack.push_back(s[i]);
    }

    for (int j = i; j < n; ++j)
        stack.push_back(s[j]);

    for (int j = 0; j < stack.size() - k; ++j)
        printf("%c", stack[j]);
    printf("\n");
    return 0;
}
