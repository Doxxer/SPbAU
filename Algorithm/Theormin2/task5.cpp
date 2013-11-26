#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>
#include <queue>
#include <climits>

using namespace std;

#define X first
#define Y second
#define MP make_pair
#define PB push_back
#define all(x) x.begin(), x.end()

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vi> vvi;

int main()
{
    // freopen("input.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    vii b(n), e(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &b[i].X, &e[i].X);
        b[i].Y = e[i].Y = i;
    }

    sort(all(b));
    b.push_back(MP(INT_MAX, 0));
    sort(all(e));
    e.push_back(MP(INT_MAX, 0));
    int i = 0, j = 0;

    queue<int> free_aud;
    int max_aud = 1;
    vi res(n);
    while (i < n || j < n) {
        if (e[j].X <= b[i].X) {
            // close
            // printf("close %d\n", e[j].X);
            free_aud.push(res[e[j].Y]);
            j++;
        } else {
            // open
            if (free_aud.size() == 0)
                free_aud.push(max_aud++);
            int aud = free_aud.front();
            free_aud.pop();
            //printf("open %d to %d\n", b[i].X, aud);
            res[b[i].Y] = aud;
            i++;
        }
    }

    printf("%d\n", max_aud - 1);
    for (int i = 0; i < n; ++i)
        printf("%d ", res[i]);
    return 0;
}
