#include "Core.h"
#include "FlowGraph.h"

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((u32)time(0));

	int n, m;
	cin >> n >> m;
	FlowGraph g(n + m);
	forh(i, 0, n) {
		int cap;
		cin >> cap;
		g.add_edge(g.src, i, cap, 0);
	}
	forh(i, n, n + m) {
		int cap;
		cin >> cap;
		g.add_edge(i, g.snk, cap, 0);
	}

	forh(i, 0, m) {
		forh(j, 0, n) {
			int cost;
			cin >> cost;
			g.add_edge(j, n + i, inf<int>(), cost);
		}
	}

	cout << g.mcmf().x << endl;

	return 0;
}
