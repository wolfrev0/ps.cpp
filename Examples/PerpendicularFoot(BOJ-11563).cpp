#include "Core.h"
#include "Line.h"
#include "ModNum.h"

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((unsigned)time(0));

	int n, m;
	cin >> n >> m;
	Segment<f64> segn[2000];
	for (int i = 0; i < n; i++){
		Vec2<f64> s, e;
		cin >> s.x >> s.y >> e.x >> e.y;
		segn[i].s(s);
		segn[i].e(e);
	}
	Segment<f64> segm[2000];
	for (int j = 0; j < m; j++){
		Vec2<f64> s, e;
		cin >> s.x >> s.y >> e.x >> e.y;
		segm[j].s(s);
		segm[j].e(e);
	}

	f64 ans = inf<int>();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			Vec2<f64> res;
			if(segm[j].perpend_foot(segn[i].s(), res))
				ans = min(ans, (segn[i].s() - res).size());
			if(segm[j].perpend_foot(segn[i].e(), res))
				ans = min(ans, (segn[i].e() - res).size());
			if(segn[i].perpend_foot(segm[j].s(), res))
				ans = min(ans, (segm[j].s() - res).size());
			if(segn[i].perpend_foot(segm[j].e(), res))
				ans = min(ans, (segm[j].e() - res).size());

			ans = min(ans, (segn[i].s() - segm[j].s()).size());
			ans = min(ans, (segn[i].s() - segm[j].e()).size());
			ans = min(ans, (segn[i].e() - segm[j].s()).size());
			ans = min(ans, (segn[i].e() - segm[j].e()).size());
		}
	}
	cout << ans << endl;

	return 0;
}