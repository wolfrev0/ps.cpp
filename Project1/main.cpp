#include "Rect.h"

pair<ll, ll> cnt(Rect r) {
	ll black = r.width() * r.height() / 2, white = r.width() * r.height() / 2;
	((r.x1 + r.y1) % 2 ? black : white) += r.width() * r.height() % 2;
	return { black, white };
}

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	ll t;
	cin >> t;
	while (t--)
	{
		ll n, m;
		cin >> n >> m;
		ll x1, x2, x3, x4, y1, y2, y3, y4;
		cin >> x1 >> y1 >> x2 >> y2;
		cin >> x3 >> y3 >> x4 >> y4;
		pair<ll, ll> base = { n * m / 2 , n * m / 2 + n * m % 2 };
		Rect r1 = { x1, y1, x2, y2 };
		Rect r2 = { x3, y3, x4, y4 };
		auto a = cnt(r1);
		a = pair<ll, ll>{ -a.first, a.first };
		auto b = cnt(r2);
		b = pair<ll, ll>{ b.second, -b.second };
		pair<ll, ll> inter = { 0,0 };
		try {
			inter = cnt(r1.intersect(r2));
		}
		catch (...) {}
		inter = pair<ll, ll>{ inter.first,-inter.first };
		auto ans = base + a + b + inter;
		cout << ans.second << ' ' << ans.first << endl;
	}

	return 0;
}