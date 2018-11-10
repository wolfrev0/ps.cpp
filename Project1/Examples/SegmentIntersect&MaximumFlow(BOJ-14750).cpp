#include "Core.h"
#include "Line.h"
#include "Graph.h"

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	int n, k, h, m;
	cin >> n >> k >> h >> m;
	MCMF g(m + h);
	vector<Segment> lines;
	Vec2 pv;
	cin >> pv.x >> pv.y;
	forh(i, 1, n)
	{
		Vec2 v;
		cin >> v.x >> v.y;
		lines.push_back(Segment{ pv, Vec2(v.x, v.y) });
		pv = Vec2(v.x, v.y);
	}
	vector<Vec2> holes;
	forh(i, 0, h)
	{
		int x, y;
		cin >> x >> y;
		holes.push_back(Vec2(x, y));
	}
	forh(i, 0, m)
	{
		Vec2 mp;
		cin >> mp.x >> mp.y;
		forh(j, 0, h)
		{
			bool fail = false;
			for (auto k : lines)
			{
				Vec2 hv = holes[j];
				hv += (mp - hv).normalize() *0.0001;
				Segment s(mp, hv);
				if (fail = k.intersect_det(s))
					break;
			}
			if (!fail)
				g.add_edge_mcmf(i, m + j, 1, 0);
		}
		g.add_edge_mcmf(g.src, i, 1, 0);
	}
	forh(i, 0, h)
		g.add_edge_mcmf(m + i, g.snk, k, 0);

	cout << (g.mcmf().second == m ? "Possible" : "Impossible") << endl;

	return 0;
}