#pragma once
#include "Core.h"

//minimum weighted bipartite matching
//NOTE: determine no matching by inf<int>()/max(n,m) instead of inf<int>().
//		or, check result's matching weight
struct Hungarian{
	Hungarian(int n, int m):n(n),m(m),g(n+1,Arr<int>(m+1,inf<int>()/max({1ll,n,m}))){}

	void add_edge(int a, int b, int c){g[a+1][b+1]=c;}
	// mat[1][1] ~ mat[n][m]
	// mat[i] : mat column of row i
	pair<int,Arr<int>> calc(){
		Arr<int> mat(n+1), u(n+1), v(m+1), p(m+1), way(m+1);
		for(int i=1;i<=n;i++){
			p[0]=i;
			int js=0;
			Arr<int> minv(m+1,inf<int>());
			Arr<bool> used(m+1);
			do{
				used[js]=true;
				int is=p[js], d=inf<int>(), je;
				for(int j=1;j<=m;j++)
					if(!used[j]){
						int c=g[is][j]-u[is]-v[j];
						if(c<minv[j]) minv[j]=c, way[j]=js;
						if(minv[j]<d) d=minv[j], je=j;
					}
				for(int j=0;j<=m;j++)
					if(used[j]) u[p[j]]+=d, v[j]-=d;
					else minv[j]-=d;
				js=je;
			}while(p[js]);
			do{
				int je=way[js];
				p[js]=p[je];
				js=je;
			}while(js);
		}
		for(int j=1;j<=m;j++)mat[p[j]]=j;
		return {-v[0],mat};
	}

	int n,m;
	Arr<Arr<int>> g;
};
