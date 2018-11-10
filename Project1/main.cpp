#include "Core.h"
#include "Line.h"
#include "ModNum.h"

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	int n, m;
	cin >> n >> m;
	Segment segn[2000];
	for (int i = 0; i < n; i++)
		cin >> segn[i].s.x >> segn[i].s.y >> segn[i].e.x >> segn[i].e.y;
	Segment segm[2000];
	for (int j = 0; j < m; j++)
		cin >> segm[j].s.x >> segm[j].s.y >> segm[j].e.x >> segm[j].e.y;

	double ans = inf<int>();
	for (int i = 0; i < n; i++)
	{
		;;
	}
	cout << ans << endl;

	return 0;
}