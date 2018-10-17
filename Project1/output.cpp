#include "bits/stdc++.h"

#define endl '\n'
#define forh(var, begin, end) for(auto var = begin; var < end; ++var)//for: half-opened range
#define forhi(var, begin, end) for(auto var = begin-1; var >= end; --var)//inversion
#define forc(var, begin, end) for(auto var = begin; var <= end; ++var)//for: closed range
#define forci(var, begin, end) for(auto var = begin; var >= end; --var)//inversion
//#pragma GCC optimize ("Ofast")

using namespace std;

using ld = long double;
using ll = long long;
using ull = unsigned long long;
using uint = unsigned;
using ushort = unsigned short;
using uchar = unsigned char;

const int mod = int(1e9 + 7);
const int prime = int(2e9 + 11);
const ld pi = acosl(-1);
const ld eps = 1e-13;
const int dirs[4][2] = { { 1, 0 },{ 0, 1 },{ -1, 0 },{ 0, -1 } };

template<typename T>
constexpr T inf() { return numeric_limits<T>::max() / 2; }


template<typename T>
struct SegmentTree
{
	SegmentTree(
		int n,
		T id = 0,
		function<T(T, T)> segf = [](T a, T b) {return a + b; },
		function<T(int, int, T, T)> lazyf = [](int l, int r, T tval, T lval) {return tval + (r - l + 1)*lval; },
		function<T(T, T)> propaf = [](T lval, T val) {return lval + val; },
		T lazy_null = inf<T>())
		//upperbound of 2^(ceil(log2(n))+1)/n is 4
		:n(n), id(id), segf(segf), lazyf(lazyf), propaf(propaf), lazy_null(lazy_null),
		tree(4 * n, id), lazy(4 * n, lazy_null)
	{}
	const int n;
	const T id;
	const function<T(T, T)> segf;
	const function<T(int, int, T, T)> lazyf;
	const function<T(T, T)> propaf;
	const T lazy_null;

	vector<T> tree;
	vector<T> lazy;

	void update(int p, T val) { update_range(1, 0, n - 1, p, p, val); }
	void update(int l, int r, T val) { update_range(1, 0, n - 1, l, r, val); }
	T query(int l, int r) { return query2(1, 0, n - 1, l, r); }
private:
	void update_lazy(int cur, int cl, int cr)
	{
		if (lazy[cur] != lazy_null)
		{
			tree[cur] = lazyf(cl, cr, tree[cur], lazy[cur]);
			if (cl != cr)
			{
				lazy[cur * 2] = propaf(lazy[cur*2], lazy[cur]);
				lazy[cur * 2 + 1] = propaf(lazy[cur * 2 + 1], lazy[cur]);
			}
			lazy[cur] = lazy_null;
		}
	}

	void update_range(int cur, int cl, int cr, int l, int r, T val)
	{
		update_lazy(cur, cl, cr);
		if (l > cr || r < cl)
			return;
		if (l <= cl && cr <= r)
		{
			lazy[cur] = propaf(lazy[cur], val);
			update_lazy(cur, cl, cr);
			return;
		}
		update_range(cur * 2, cl, (cl + cr) / 2, l, r, val);
		update_range(cur * 2 + 1, (cl + cr) / 2 + 1, cr, l, r, val);
		tree[cur] = segf(tree[cur * 2], tree[cur * 2 + 1]);
	}

	T query2(int cur, int cl, int cr, int l, int r)
	{
		update_lazy(cur, cl, cr);
		if (l > cr || r < cl)
			return id;
		if (l <= cl && cr <= r)
			return tree[cur];
		return segf(query2(cur * 2, cl, (cl + cr) / 2, l, r), query2(cur * 2 + 1, (cl + cr) / 2 + 1, cr, l, r));
	}
};

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	SegmentTree<ll> st(1000000, 1, [](auto a, auto b) {return (a * b) % mod; }, [](int l, int r, auto a, auto b) {return b; }, [](auto a, auto b) {return b; });
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++)
	{
		ll x;
		cin >> x;
		st.update(i, x);
	}
	for (int i = 0; i < m + k; i++)
	{
		int a, b;
		ll c;
		cin >> a;
		if (a == 1)
		{
			cin >> b >> c;
			st.update(--b, c);
		}
		else
		{
			cin >> b >> c;
			cout << st.query(--b, --c) << endl;
		}
	}

	return 0;
}
