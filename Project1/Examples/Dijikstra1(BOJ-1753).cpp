#include "Core.h"
#include "Graph.h"

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	int v, e;
	cin >> v >> e;
	int s;
	cin >> s;
	s--;
	WeightedGraph<int> g(v);
	forh(i, 0, e)
	{
		int a, b, c;
		cin >> a >> b >> c;
		a--, b--;
		g.add_edge(a, b, c);
	}
	vector<int> d;
	vector<pair<int, int>> p;
	g.spfa(d, p, s);
	forh(i, 0, v)
		if (d[i] == inf<int>())
			cout << "INF" << endl;
		else
			cout << d[i] << endl;

	return 0;
}