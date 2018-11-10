#include "Graph.h"
#include "Line.h"

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	int n, m;
	cin >> n >> m;
	MCMF g(n + m);
	forh(i, 0, n)
	{
		int cnt;
		cin >> cnt;
		for (int j = 0; j < cnt; j++)
		{
			int x;
			cin >> x;
			x--;
			g.add_edge_mcmf(i, n + x, 1, 0);
		}
		g.add_edge_mcmf(g.src, i, 1, 0);
	}
	forh(i, n, n + m)
		g.add_edge_mcmf(i, g.snk, 1, 0);

	cout << g.mf() << endl;

	return 0;
}