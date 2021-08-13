#pragma once
#include "core/base.h"

template<class T> struct Bipartite {
	Arr<T> a[2];
	Bipartite(int n, int m) {}

	void add_edge(int a, int b, int w) {}

	// low constant rather than mcmf_fast
	// maybe useful because of cache optimizaion, etc
	// int hungarian(){}

	// low constant rather than dinic
	// maybe useless because almost same with dinic
	// int hopcroft_karp(){}
};

// NOTE: minimum weighted bipartite matching
//NOTE: 단순히 가중치를 음수로 바꾸면 max매칭이 되는게 맞는데 어째선지 잘 안됨(TLE남). 일단 max매칭은 mcmf로 풀자
// NOTE: determine no matching by inf<int>()/max(n,m) instead of inf<int>().
//		or, check result's matching weight
struct Hungarian {
	Hungarian(int n, int m)
	    : n(n), m(m), g(n + 1, Arr<int>(m + 1, inf<int>() / max({1ll, (i64)n, (i64)m}))) {}

	void add_edge(int a, int b, int c) { g[a + 1][b + 1] = c; }
	// mat[1][1] ~ mat[n][m]
	// mat[i] : mat column of row i
	pair<int, Arr<int>> calc() {
		Arr<int> mat(n + 1), u(n + 1), v(m + 1), p(m + 1), way(m + 1);
		for(int i = 1; i <= n; i++) {
			p[0] = i;
			int js = 0;
			Arr<int> minv(m + 1, inf<int>());
			Arr<char> used(m + 1);
			do {
				used[js] = true;
				int is = p[js], d = inf<int>(), je;
				for(int j = 1; j <= m; j++)
					if(!used[j]) {
						int c = g[is][j] - u[is] - v[j];
						if(c < minv[j]) minv[j] = c, way[j] = js;
						if(minv[j] < d) d = minv[j], je = j;
					}
				for(int j = 0; j <= m; j++)
					if(used[j]) u[p[j]] += d, v[j] -= d;
					else
						minv[j] -= d;
				js = je;
			} while(p[js]);
			do {
				int je = way[js];
				p[js] = p[je];
				js = je;
			} while(js);
		}
		for(int j = 1; j <= m; j++) mat[p[j]] = j;
		return {-v[0], mat};
	}

	int n, m;
	Arr<Arr<int>> g;
};
