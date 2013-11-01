#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

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

bool comp(ii a, ii b)
{
    if (a.X != b.X)
        return a.X < b.X;
    return a.Y < b.Y;
}

int main()
{
    freopen("input.txt", "r", stdin);
    int n, k;
    scanf("%d", &n);
    vi a(n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i]);
    scanf("%d", &k);

    // median
    int med_index = (n - 1) / 2;
    nth_element(a.begin(), a.begin() + med_index, a.end());
    int med = a[med_index];

    // find k closest by distance
    int left_index = (n - k) / 2;
    int right_index = (n + k) / 2 - 1;

    nth_element(a.begin(), a.begin() + left_index, a.end());
    int left = a[left_index];
    int count_left =
        count(a.begin(), a.end(), left) - count(a.begin(), a.begin() + left_index, left);
    // printf("left = %d, left_index = %d, count_left = %d\n", left, left_index, count_left);

    nth_element(a.begin(), a.begin() + right_index, a.end());
    int right = a[right_index];
    int count_right = count(a.rbegin(), a.rend(), right) -
                      count(a.rbegin(), a.rbegin() + n - 1 - right_index, right);
    // printf("right = %d, right_index = %d, count_right = %d\n", right, right_index, count_right);

    if (count_right + count_left > k) {
        for (int i = 0; i < k; ++i)
            printf("%d ", med);
    } else {
        for (int i = 0; i < count_left; ++i)
            printf("%d ", left);
        for (int i = 0; i < count_right; ++i)
            printf("%d ", right);
        if (count_left + count_right < k) {
            for (int i = 0; i < n; ++i) {
                if (a[i] > left && a[i] < right)
                    printf("%d ", a[i]);
            }
        }
    }
    printf("\n");

    // find k closest by value
    vii r(n);
    for (int i = 0; i < n; ++i)
        r[i] = MP(abs(a[i] - med), a[i]);
    nth_element(r.begin(), r.begin() + k - 1, r.end(), comp);
    for (int i = 0; i < k; ++i)
        printf("%d ", r[i].Y);
    printf("\n");
    return 0;
}
