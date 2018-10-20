#include "Geometry.h"

void error()
{
	cout << -1 << endl;
	exit(0);
}

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(0);
	srand((uint)time(0));

	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		Polygon p(n);
		forh(i, 0, n)
			cin >> p[i].x >> p[i].y;
		p.sort();
		p = p.convex_hull();

		int j = 1;
		Vec2 a1 = p[0], a2 = p[1];
		forh(i, 0, p.size())
		{
			int ni = (i + 1) % p.size();
			int nj = (j + 1) % p.size();
			while ((p[ni] - p[i]).cross(p[nj] - p[j]) > 0)
				j = nj, nj = (nj + 1) % p.size();
			if ((a1 - a2).sizesq() < (p[j] - p[i]).sizesq())
				a1 = p[i], a2 = p[j];
		}
		cout << a1.x << ' ' << a1.y << ' ' << a2.x << ' ' << a2.y << endl;
	}

	return 0;
}
