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
	forh(i, 0, 3)
	{
		Vec2 v;
		cin >> v.x >> v.y;
		cout << p.contains(v) << endl;
	}

	return 0;
}