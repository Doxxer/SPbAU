#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

int main()
{
    freopen("input.txt", "r", stdin);
    ull n;
    cin >> n;

    ull left = 1, right = n + 1;
    ull mid = left + (right - left) / 2;

    while (left < right) {
        if (mid > n / mid) {
            right = mid + 1;
        } else {

            left = mid - 1;
        }
        mid = left + (right - left) / 2;
    }

    cout << left << endl << right << endl;
    return 0;
}
