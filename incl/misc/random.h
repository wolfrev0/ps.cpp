#pragma once
#include "core/base.h"

// Random
mt19937 _rng(i64(new int)^time(0));
int rd(){static uniform_int_distribution<int> dist(0,inf<int>());return dist(_rng);}
int rd(int e){return rd()%e;}
int rd(int s,int e){return rd()%(e-s)+s;}
f64 rdf(){static uniform_real_distribution<f64> dist(0,1);return dist(_rng);}
void shuffle(auto is,auto ie){shuffle(is,ie,_rng);}

//0이상 sum이하 랜덤. 1이상 필요하면 미리 n만큼 빼두고 구한다음 나중에 +1
Arr<int> rdarrsum(int n,int sum){
	Arr<int> p;
	p.emplace_back(0);
	for(int i=0;i<n-1;i++)
		p.emplace_back(rd(0,sum+1));
	p.emplace_back(sum);
	sort(p.begin(),p.end());
	Arr<int> arr;
	for(int i=1;i<sz(p);i++)
		arr.emplace_back(p[i]-p[i-1]);
	return arr;}