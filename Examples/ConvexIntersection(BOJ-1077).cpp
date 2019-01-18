#include "Core.h"
#include "Polygon.h"

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	int n, m;
	cin >> n >> m;
	Convex<ld> p1, p2;
	forh(i, 0, n)
	{
		Vec2<ld> v;
		cin >> v.x >> v.y;
		p1.pushb(v);
	}
	forh(i, 0, m)
	{
		Vec2<ld> v;
		cin >> v.x >> v.y;
		p2.pushb(v);
	}
	cout << p1.intersect(p2).area() << endl;

	return 0;
}