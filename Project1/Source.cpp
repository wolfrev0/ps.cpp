#include "Graph.h"

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	int n, m;
	cin >> n >> m;
	Graph g(n);
	forh(i, 0, m)
	{
		int x;
		cin >> x;
		int p;
		cin >> p;
		p--;
		forh(i, 1, x)
		{
			int c;
			cin >> c;
			c--;
			g.add_edge(c, p);
			p = c;
		}
	}

	auto ans = g.topo_sort();
	if (ans.empty())
		cout << 0 << endl;
	else
		for (auto i : ans)
			cout << i + 1 << endl;

	return 0;
}