#include "Core.h"
#include "Line.h"
#include "FlowGraph.h"

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((unsigned)time(0));

	int n, k, h, m;
	cin >> n >> k >> h >> m;
	FlowGraph g(m + h);
	vector<Segment<f64>> lines;
	Vec2<f64> pv;
	cin >> pv.x >> pv.y;
	forh(i, 1, n)
	{
		Vec2<f64> v;
		cin >> v.x >> v.y;
		lines.emplace_back(pv, v);
		pv = Vec2<f64>(v.x, v.y);
	}
	vector<Vec2<f64>> holes;
	forh(i, 0, h)
	{
		int x, y;
		cin >> x >> y;
		holes.emplace_back(x, y);
	}
	forh(i, 0, m)
	{
		Vec2<f64> mp;
		cin >> mp.x >> mp.y;
		forh(j, 0, h)
		{
			bool fail = false;
			for (auto k : lines)
			{
				Vec2<f64> hv = holes[j];
				hv += (mp - hv).normalize() *0.0001;
				Segment s(mp, hv);
				if (fail = k.intersect_det(s))
					break;
			}
			if (!fail)
				g.add_edge(i, m + j, 1, 0);
		}
		g.add_edge(g.src, i, 1, 0);
	}
	forh(i, 0, h)
		g.add_edge(m + i, g.snk, k, 0);

	cout << (g.mf() == m ? "Possible" : "Impossible") << endl;

	return 0;
}