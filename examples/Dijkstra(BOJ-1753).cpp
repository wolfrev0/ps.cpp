#include "Core.h"
#include "Graph.h"

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((unsigned)time(0));

	int v, e;
	cin >> v >> e;
	int s;
	cin >> s;
	s--;
	Graph<int> g(v);
	hfor(i, 0, e)
	{
		int a, b, c;
		cin >> a >> b >> c;
		a--, b--;
		g.add_edge(a, b, c);
	}
	vector<int> d;
	vector<Graph<int>::Edge> p;
	g.dijkstra(d, p, s);
	hfor(i, 0, v)
		if (d[i] == inf<int>())
			cout << "INF" << endl;
		else
			cout << d[i] << endl;

	return 0;
}