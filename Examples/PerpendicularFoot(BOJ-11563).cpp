#include "Core.h"
#include "Line.h"
#include "ModNum.h"

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((u32)time(0));

	int n, m;
	cin >> n >> m;
	Segment<F64> segn[2000];
	for (int i = 0; i < n; i++){
		Vec2<F64> s, e;
		cin >> s.x.n >> s.y.n >> e.x.n >> e.y.n;
		segn[i].s(s);
		segn[i].e(e);
	}
	Segment<F64> segm[2000];
	for (int j = 0; j < m; j++){
		Vec2<F64> s, e;
		cin >> s.x.n >> s.y.n >> e.x.n >> e.y.n;
		segm[j].s(s);
		segm[j].e(e);
	}

	f64 ans = I32::inf();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			Vec2<F64> res;
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