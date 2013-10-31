#include <iostream>
#include <cstddef>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

struct person {
    person(string s, int l, int r) : name(s), left(l), right(r)
    {
    }
    string name;
    int left;
    int right;
};

int main()
{
    freopen("input.txt", "r", stdin);
    int n, k;
    string s;
    cin >> n;

    vector<person> v;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        v.push_back(person(s, i == 0 ? n - 1 : i - 1, i == n - 1 ? 0 : i + 1));
    }

    for (int i = 0; i < n - 3; ++i) {
        cin >> k;
        --k;
        person cur = v[k];
        printf("%s %s\n", v[cur.left].name.data(), v[cur.right].name.data());
        // update
        v[cur.left].right = cur.right;
        v[cur.right].left = cur.left;
    }
    return 0;
}
