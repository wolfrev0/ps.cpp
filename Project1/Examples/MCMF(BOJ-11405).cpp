#include "Core.h"
#include "Graph.h"

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	int n, m;
	cin >> n >> m;
	MCMF g(n + m);
	forh(i, 0, n)
	{
		int cap;
		cin >> cap;
		g.add_edge_mcmf(g.src, i, cap, 0);
	}
	forh(i, n, n + m)
	{
		int cap;
		cin >> cap;
		g.add_edge_mcmf(i, g.snk, cap, 0);
	}

	forh(i, 0, m)
	{
		forh(j, 0, n)
		{
			int cost;
			cin >> cost;
			g.add_edge_mcmf(j, n + i, inf<int>(), cost);
		}
	}

	int ans = 0;
	while (auto res = g.mcmf().first)
		ans += res;
	cout << ans << endl;

	return 0;
}