#include "bits/stdc++.h"
#define endl '\n'
#define forh(var, begin, end) for(auto var = begin; var < end; ++var)//for: half-opened range
#define forhi(var, begin, end) for(auto var = end-1; var >= begin; --var)//inversion
#define forc(var, begin, end) for(auto var = begin; var <= end; ++var)//for: closed range
#define forci(var, begin, end) for(auto var = end; var >= begin; --var)//inversion
#pragma GCC optimize ("Ofast")

using namespace std;
using namespace std::placeholders;

using ld = double;
using ll = long long;
using ull = unsigned long long;
using uint = unsigned;
using ushort = unsigned short;
using uchar = unsigned char;

const int mod = int(1e9 + 7);
const int prime = int(2e9 + 11);
const ld pi = acos(-1);
const ld eps = 1e-12;
const int dir[4][2] = { { 1, 0 },{ 0, 1 },{ -1, 0 },{ 0, -1 } };

template<typename T>
constexpr inline T inf() { return numeric_limits<T>::max() / 2; }

struct Graph {
	vector<vector<int>> g;
	vector<int> in;

	Graph(int n) :g(n), in(n) {}

	inline void add_edge(int s, int e) {
		g[s].push_back(e);
		in[e]++;
	}

	vector<int> topo_sort() {
		queue<int> q;
		forh(i, 0u, g.size())
			if (!in[i])
				q.push(i);
		vector<int> ret;
		while (q.size()) {
			auto cur = q.front();
			ret.push_back(cur);
			q.pop();
			for (auto i : g[cur])
				if (--in[i] == 0)
					q.push(i);
		}
		reverse(ret.begin(), ret.end());
		forh(i, 0u, g.size())
			if (in[i])
				throw "Error";
		return ret;
	}
	//dfs()
	//bfs()
	//maybe useless?
};

template<typename T>
struct WeightedGraph {
	struct Edge {
		int v;
		T w;
	};
	const int n;
	vector<vector<Edge>> g;

	WeightedGraph(int n) :n(n), g(n) {}

	inline void add_edge(int s, int e, T w) { g[s].push_back({ e, w }); }

	void dijikstra(vector<T> &d, vector<pair<int, int>> &p, int s) {
		priority_queue < pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;//dest, v
		d.resize(n, inf<int>());
		p.resize(n, { -1, -1 });
		d[s] = 0;
		pq.push({ 0, s });
		while (!pq.empty())
		{
			auto cur = pq.top();
			pq.pop();

			if (cur.first != d[cur.second])
				continue;

			auto &cg = g[cur.second];
			forh(i, 0u, cg.size())
			{
				if (d[cg[i].v] > cur.first + cg[i].w) {
					d[cg[i].v] = cur.first + cg[i].w;
					p[cg[i].v] = { cur.second, i };
					pq.push({ cur.first + cg[i].w,cg[i].v });
				}

			}
		}
	}

	bool spfa(vector<T> &ub, vector<pair<int, int>> &p, int s) {
		queue<int> q;
		vector<bool> inq(n);
		ub.resize(n, inf<int>());
		p.resize(n, { -1, -1 });

		ub[s] = 0;
		inq[s] = true;
		q.push(s);
		int i;
		for (i = 0; i < n && q.size(); i++) {
			int qsz = q.size();
			while (qsz--) {
				int j = q.front();
				inq[j] = false;
				q.pop();
				forh(k, 0u, g[j].size())
					if (valid_spfa_edge(g[j][k]) && ub[j] + g[j][k].w < ub[g[j][k].v]) {
						p[g[j][k].v] = { j, k };
						ub[g[j][k].v] = ub[j] + g[j][k].w;
						if (!inq[g[j][k].v]) {
							inq[g[j][k].v] = true;
							q.push(g[j][k].v);
						}
					}
			}
		}
		return q.empty();
	}

	virtual bool valid_spfa_edge(const Edge &w) const { return true; }
};

struct MCMFWeight {
	uint revi;
	int cap, cost;
	MCMFWeight(int cost) :cost(cost) {}
	MCMFWeight(uint revi, int cap, int cost) :revi(revi), cap(cap), cost(cost) {}
	bool operator< (const MCMFWeight &r)const { return cost < r.cost; }
	MCMFWeight operator+(const MCMFWeight &r)const { return cost + r.cost; }
};

struct MCMF : public WeightedGraph<MCMFWeight>
{
	const int src, snk;

	MCMF(int n) :WeightedGraph(n + 2), src(n), snk(n + 1) {}

	inline void add_edge_mcmf(uint s, uint e, int cap, int cost) {
		WeightedGraph::add_edge(s, e, { g[e].size(), cap, cost });
		WeightedGraph::add_edge(e, s, { g[s].size() - 1, 0, -cost });
	}

	pair<int, int> process() {
		pair<int, int> ret = { 0,0 };
		int &flow = ret.second;
		flow = inf<int>();

		vector<MCMFWeight> ub;
		vector<pair<int, int>> p;
		if (!spfa(ub, p, src) || p[snk].first == -1)
			return { 0, 0 };
		for (int cur = snk; p[cur].first != -1; cur = p[cur].first)
			flow = min(flow, g[p[cur].first][p[cur].second].w.cap);
		for (int cur = snk; p[cur].first != -1; cur = p[cur].first) {
			auto &e = g[p[cur].first][p[cur].second];
			e.w.cap -= flow;
			g[e.v][e.w.revi].w.cap += flow;
			ret.first += e.w.cost*flow;
		}

		return ret;
	}

	pair<int, int> mcmf() {
		pair<int, int> ret = { 0, 0 };
		while (true) {
			auto res = process();
			if (!res.first && !res.second)
				break;
			ret.first += res.first;
			ret.second += res.second;
		}
		return ret;
	}

	virtual bool valid_spfa_edge(const Edge &e) const override { return e.w.cap; }
};

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	int n, m;
	cin >> n >> m;
	WeightedGraph<int> g(n);
	forh(i, 0, m) {
		int a, b, c;
		cin >> a >> b >> c;
		a--, b--;
		g.add_edge(a, b, c);
		g.add_edge(b, a, c);
	}
	forh(i, 0, n) {
		vector<int> d;
		vector<pair<int, int>> p;
		g.dijikstra(d, p, i);
		forh(j, 0, n) {
			if (i == j)
				cout << '-' << ' ';
			else {
				int v = j;
				while (p[v].first != i)
					v = p[v].first;
				cout << v + 1 << ' ';
			}
		}
		cout << endl;
	}

	return 0;
}
