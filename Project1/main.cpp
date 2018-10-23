#include "Geometry.h"

void error()
{
	cout << -1 << endl;
	exit(0);
}

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	int n;
	cin >> n;
	Polygon p(n);
	forh(i, 0, n)
		cin >> p[i].x >> p[i].y;

	ll ans = 0;
	forh(i, 0, n)
	{
		p.sort();
		int j = (i + 1) % n;
	}
	cout << ans / 2 << endl;

	return 0;
}