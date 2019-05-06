#include "Core.h"
#include "Graph.h"

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((u32)time(0));

	int n, m;
	cin >> n >> m;
	Graph<int> g(n);
	forh(i, 0, m) {
		int a, b, c;
		cin >> a >> b >> c;
		a--, b--;
		g.add_edge(a, b, c);
		g.add_edge(b, a, c);
	}
	forh(i, 0, n) {
		vector<int> d;
		vector<Pair<int, int>> p;
		g.dijkstra(d, p, i);
		forh(j, 0, n) {
			if (i == j)
				cout << '-' << ' ';
			else {
				int v = j;
				while (p[v].a != i)
					v = p[v].a;
				cout << v + 1 << ' ';
			}
		}
		cout << endl;
	}

	return 0;
}