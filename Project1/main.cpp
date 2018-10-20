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
	Polygon polygon(n);
	forh(i, 0, n)
		cin >> polygon[i].x >> polygon[i].y;
	polygon.sort();
	cout << polygon.convex_hull().size() << endl;

	return 0;
}