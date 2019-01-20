#include "Core.h"
#include "Graph.h"

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((u32)time(0));

	int v, e;
	cin >> v >> e;
	int s;
	cin >> s;
	s--;
	Graph<I32> g(v);
	forh(i, 0, e)
	{
		int a, b, c;
		cin >> a >> b >> c;
		a--, b--;
		g.add_edge(a, b, c);
	}
	vector<I32> d;
	vector<pair<int, int>> p;
	g.dijkstra(d, p, s);
	forh(i, 0, v)
		if (d[i] == I32::inf())
			cout << "INF" << endl;
		else
			cout << d[i] << endl;

	return 0;
}