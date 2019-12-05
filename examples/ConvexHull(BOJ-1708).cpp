#include "Core.h"
#include "Polygon.h"

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(12);
	srand((unsigned)time(0));

	int n;
	cin >> n;
	Convex<i64> c(n);
	forh(i, 0, n)
		cin >> c[i].x >> c[i].y;
	c.normalize();
	cout << c.size() << endl;

	return 0;
}