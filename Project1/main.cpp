#include "Core.h"
#include "Graph.h"

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	int n;
	cin >> n;
	WeightedGraph<int> g(n);
	int m;
	cin >> m;
	forh(i, 0, m)
	{
		int a, b, c;
		cin >> a >> b >> c;
		a--, b--;
		g.add_edge(a, b, c);
		g.add_edge(b, a, c);
	}
	const auto &edges = g.mst_kruskal();
	int ans = 0;
	for (auto &i : edges)
		ans += g.g[i.first][i.second].w;
	cout << ans << endl;

	return 0;
}