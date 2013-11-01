#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

#define X first
#define Y second
#define MP make_pair
#define PB push_back

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef vector<bool> vb;
typedef vector<pll> vpll;

vb prime;

void sieve(ll n)
{
    ll k = ll(sqrt(n)) + 1;
    prime.assign(k, true);
    prime[0] = prime[1] = false;
    for (ll j = 4; j < k; j += 2)
        prime[j] = false;
    for (ll i = 3; i < k; i += 2)
        if (prime[i])
            for (ll j = i * i; j < k; j += i)
                prime[j] = false;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    ull n;
    cin >> n;

    if (n == 1) {
        cout << 0 << endl;
        return 0;
    }

    sieve(n);

    vpll res;
    for (size_t i = 2; i < prime.size() && n > 1; ++i)
        if (prime[i] && !(n % i)) {
            ll c = 0;
            while (!(n % i)) {
                n /= i;
                c++;
            }
            res.PB(MP(i, c));
        }
    if (n > 1)
        res.PB(MP(n, 1));
    cout << res.size() << endl;
    for (size_t i = 0; i < res.size(); ++i)
        cout << res[i].X << " " << res[i].Y << endl;
    return 0;
}
