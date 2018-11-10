#include "Graph.h"
#include "Line.h"

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	int n, m;
	cin >> n >> m;
	MCMF g(n + n);
	forh(i, 0, m)
	{
		int a, b;
		cin >> a >> b;
		a--, b--;
		g.add_edge_mcmf(a, n + b, 1, 0);
	}
	forh(i, 0, n)
	{
		g.add_edge_mcmf(g.src, i, 1, 0);
		g.add_edge_mcmf(n + i, g.snk, 1, 0);
	}

	cout << g.mf() << endl;

	return 0;
}