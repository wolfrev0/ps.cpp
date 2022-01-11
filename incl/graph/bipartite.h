#pragma once
#include "core/base.h"

template<class T> struct Bipartite{
	Arr<T> a[2];
	Bipartite(int n,int m){}

	void add_edge(int a,int b,int w){}

	// low constant rather than mcmf_fast
	// maybe useful because of cache optimizaion,etc
	// int hungarian(){}

	// low constant rather than dinic
	// maybe useless because almost same with dinic
	// int hopcroft_karp(){}
};

//NOTE: self loop=0들어가는 경우 주의하자. 매칭값 0이됨
//NOTE: minimum weighted bipartite matching
//NOTE: 단순히 가중치를 음수로 바꾸면 max매칭이 되는게 맞는데 어째선지 잘 안됨(TLE남). 일단 max매칭은 mcmf로 풀자
//NOTE: 매칭안된거 판별을 inf<int>()대신 inf<int>()/max(n,m)써야 오버플로 안나는듯? 아니면 매칭결과의 가중치 확인으로도 가능
struct Hungarian{
	using T=i64;
	Hungarian(int n,int m):n(n),m(m),g(n+1,Arr<T>(m+1,inf<int>()/max({1ll,(i64)n,(i64)m}))){}

	void add_edge(int a,int b,T c){g[a+1][b+1]=c;}
	// mat[1][1] ~ mat[n][m]
	// mat[i] : mat column of row i
	pair<T,Arr<int>> calc(){
		Arr<int> mat(n+1),p(m+1),way(m+1);
		Arr<T> u(n+1),v(m+1);
		for(int i=1;i<=n;i++){
			p[0]=i;
			int js=0;
			Arr<T> minv(m+1,inf<int>());
			Arr<char> used(m+1);
			do{
				used[js]=true;
				int is=p[js],je;T d=inf<int>();
				for(int j=1;j<=m;j++)
					if(!used[j]){
						T c=g[is][j] - u[is] - v[j];
						if(c < minv[j])minv[j]=c,way[j]=js;
						if(minv[j] < d)d=minv[j],je=j;
					}
				for(int j=0;j<=m;j++)
					if(used[j])u[p[j]]+=d,v[j]-=d;
					else minv[j]-=d;
				js=je;
			} while(p[js]);
			do{
				int je=way[js];
				p[js]=p[je];
				js=je;
			} while(js);
		}
		for(int j=1;j<=m;j++)mat[p[j]]=j;
		return{-v[0],mat};
	}
	int n,m;
	Arr<Arr<T>> g;
};
