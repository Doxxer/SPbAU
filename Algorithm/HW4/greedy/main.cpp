#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <climits>
#include <cstring>
#include <cctype>
#include <ctime>
#include <sstream>
#include <cassert>
#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <queue>
using namespace std;

// <editor-fold defaultstate="collapsed" desc="Defines">

typedef long long ll;
typedef unsigned long long ull;
typedef pair<double, double> dd;
typedef pair<double, int> di;
typedef pair<int, int> ii;
typedef pair<ii, int> box;
typedef pair<ll, ll> pll;
typedef pair<string, int> si;
typedef pair<double, ll> pdl;
typedef map<int, int> mi;
typedef map<string, int> msi;
typedef map<string, string> mss;
typedef map<char, int> mci;
typedef set<int> sei;
typedef vector<si> vsi;
typedef vector<dd> vdd;
typedef vector<char> vc;
typedef vector<double> vd;
typedef vector<bool> vb;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<ull> vull;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<string> vs;
const double PI = 3.14159265358979;
const double PI2 = 6.28318530717958;
const double PId2 = 1.570796326794895;
#define PB push_back
#define MP make_pair
#define X first
#define Y second
#define eps 1E-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()

template<typename T> T sqr(T x)
{
	return x*x;
}

template<typename T> T gcd(T a, T b)
{
	return (b ? gcd(b, a % b) : a);
}

ll pw(ll a, ll p, ll mod)
{
	ll res = 1;
	while (p) {
		if (p & 1) {
			--p;
			res = (res * a) % mod;
		} else {
			p >>= 1;
			a = (a * a) % mod;
		}
	}
	return res;
}

inline vi ReadVI(int count)
{
	vi array(count);
	for (int i = 0; i < count; i++)
		scanf("%d", &array[i]);
	return array;
}

inline vll ReadVlong(int count)
{
	vll arrayname(count);
	for (int i = 0; i < count; i++) cin >> arrayname[i];
	return arrayname;
}

const int MOD = 1000000007;
const int MOD2 = 1073741824;
const int MAXVALUE = 200010;

// </editor-fold >

bool cmpW(const ii &a, const ii &b)
{
	if (a.X != b.X)
		return a.X > b.X;
	return a.Y > b.Y;	
}

void generateTest()
{
	FILE* f = fopen("input.txt", "w+");
	int n = (rand() % 200 + 1);
	int q = 2*n-1;
	fprintf(f, "%d\n", q);
	for (int i = 0; i < q; ++i)
	{
		int w = rand() % 100;
		int b = rand() % 100;
		fprintf(f, "%d %d\n", w, b);
	}
	fclose(f);
}


bool Solve(bool v = false)
{
	freopen("input.txt", "r", stdin);
	
	int n = 0;
	cin >> n;
	int q = (n+1)/2;
	vii a(n);
	
	int sumW = 0, sumB = 0;
	for(size_t i = 0; i < n; ++i)
	{
		ii t;
		scanf("%d %d", &t.X, &t.Y);
		a[i] = t;
		sumW += t.X;
		sumB += t.Y;
	}
	// fclose(stdin);
	
	sort(all(a), cmpW);	
	vi t(n, 0);
	
	// init
	for(size_t i = 0; i < n; i+=2)
		t[i] = 1;
	
	for(size_t i = 1; i < n; i++)
	{
		if (t[i] == 1)
		{
			if (a[i-1].Y > a[i].Y)
			{
				t[i] = 0;
				t[i-1] = 1;
			}
		}
	}
		
	// CHECK
	int wSel = 0, bSel = 0;	
	for(size_t i = 0; i < n; ++i)
	{
		if (t[i] == 1)
		{
			wSel += a[i].X;
			bSel += a[i].Y;
		}
	}
	
	if (v)
		printf("%d/%d %d/%d\n", wSel, sumW, bSel, sumB);
	
	if (wSel*2 >= sumW && bSel*2 >= sumB)
		return true;
	
	if (v)
		for(size_t i = 0; i < n; ++i)
			if (t[i] == 1)
				printf("%d-%d\n", a[i].X, a[i].Y);
	return false;	
}

int main()
{
	
	srand(time(0));
	
	int T = 100;
	for(size_t i = 0; i < T; ++i)
	{
		generateTest();
		
		if (!Solve())
		{
			printf("FAIL AT Test %ld. BREAK\n", i);
			return 1;
		}
		if (!(i % 1000))
			printf("test %ld passed!\n", i);
	}	
	printf("passed all %d tests!\n", T);	
	return 0;
}
