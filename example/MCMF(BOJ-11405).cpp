#include "FlowGraph.h"
#define endl '\n'//not interactive?
//#define int i64//overflow?

signed main(){
	int n, m;
	cin >> n >> m;
	FlowGraph g(n + m);
	hfor(i, 0, n) {
		int cap;
		cin >> cap;
		g.add_edge(g.src, i, cap, 0);
	}
	hfor(i, n, n + m) {
		int cap;
		cin >> cap;
		g.add_edge(i, g.snk, cap, 0);
	}

	hfor(i, 0, m) {
		hfor(j, 0, n) {
			int cost;
			cin >> cost;
			g.add_edge(j, n + i, inf<int>(), cost);
		}
	}

	cout << g.mcmf().first << endl;

	return 0;
}
