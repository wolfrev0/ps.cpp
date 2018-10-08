#include "Geometry.h"

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	int n;
	cin >> n;
	vector<Vec2> arr(n);
	forh(i, 0, n)
		cin >> arr[i].x >> arr[i].y;
	cout << convex_hull(arr).size() << endl;

	return 0;
}