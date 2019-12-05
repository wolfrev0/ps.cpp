#pragma once
#include "Graph.h"

template<typename T>
struct Bipartite{
	Arr<T> a[2];
	Bipartite(int n, int m){}
	
	void add_edge(int a, int b, int w){}
	
	//low constant rather than mcmf_fast
	//maybe useful because of cache optimizaion, etc
	int hungarian(){}
	
	//low constant rather than dinic
	//maybe useless because almost same with dinic
	int hopcroft_karp(){}
};