#include "Core.h"
#include "Polygon.h"

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	int n, m;
	cin >> n >> m;
	Convex p1, p2;
	forh(i, 0, n)
	{
		int x, y;
		cin >> x >> y;
		p1.pushback(Vec2(x, y));
	}
	forh(i, 0, m)
	{
		int x, y;
		cin >> x >> y;
		p2.pushback(Vec2(x, y));
	}
	cout << p1.intersect(p2).area() << endl;

	return 0;
}