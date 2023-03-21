#pragma once
#include "misc/random.h"

namespace gen{
	Arr<int> seq(int n,int min,int max){
		Arr<int> a(n);
		for(auto&i:a)
			i=rd(min,max+1);
		return a;
	}

	Arr<int> seq_sum(int n,int sum,int min){
		//max=n-min*(n-1)
		sum-=min*n;//watch out for overflow
		Arr<int> p;
		p.emplace_back(0);
		for(int i=0;i<n-1;i++)
			p.emplace_back(rd(0,sum+1));
		p.emplace_back(sum);
		sort(p.begin(),p.end());
		Arr<int> arr;
		for(int i=1;i<sz(p);i++)
			arr.emplace_back(p[i]-p[i-1]+min);
		return arr;
	}

	Arr<int> permu(int n){
		Arr<int> a(n);
		iota(a.begin(),a.end(),0);
		shuffle(a.begin(),a.end());
		return a;
	}

	Arr<pint> tree(int n,function<int(int)> fidx=lamp(rd(idx),int idx)){
		Arr<pint> a;
		auto b=permu(n);
		for(int i=1;i<n;i++)
			a.emplace_back(b[fidx(i)],b[i]);
		shuffle(a.begin(),a.end());
		return a;
	}
	Arr<pint> star(int n, fp randomness=0){
		return tree(n,lam(rdf()<randomness?rd(idx):0,int idx));
	}
	Arr<pint> bamboo(int n, fp randomness=0){
		return tree(n,lam(rdf()<randomness?rd(idx):idx-1,int idx));
	}

	template<bool simple=true,bool loop=false>
	Arr<pint> graph(int v,int e){
		//if not simple, graph can have (self-loop, multi-edge, disconnection)
		static_assert(!simple or !loop); //'simple&&loop==true' is non-sense
		Arr<pint> a;
		if(v<5000){
			if(simple){
				for(int i=0;i<v;i++)
					for(int j=0;j<i;j++)
						a.emplace_back(i,j);
				shuffle(a.begin(),a.end());
				a.erase(a.begin()+e,a.end());
			}else{
				for(int i=0;i<e;i++){
					int x,y;
					do{
						x=rd(v);
						y=rd(v);
					}while(!loop and x==y);
					a.emplace_back(x,y);
				}
			}
		}else{
			set<pint> z;
			if(simple){
				for(auto [x,y]:tree(v))
					z.emplace(min(x,y),max(x,y));
			}
			while(sz(z)<e){
				int x,y;
				do{
					x=rd(v);
					y=rd(v);
				}while(!loop && x==y);
				z.emplace(min(x,y),max(x,y));
			}
			for(auto [x,y]:z)
				a.emplace_back(rd(2)?mkp(x,y):mkp(y,x));
		}
		shuffle(a.begin(),a.end());
		return a;
	}
	Arr<pint> grid(int n,int m){
		//v=n*m, e=(n-1)*m+n*(m-1)
		Arr<pint> a;
		auto b=permu(n*m);
		for(int i=0;i<n;i++)
			for(int j=0;j<m-1;j++)
				a.emplace_back(b[i*m+j], b[i*m+j+1]);
		for(int j=0;j<m;j++)
			for(int i=0;i<n-1;i++)
				a.emplace_back(b[i*m+j], b[(i+1)*m+j]);
		shuffle(a.begin(),a.end());
		return a;
	}
	Arr<pint> bicross(int v){
		//e ~= 1.5v
		Arr<pint> a;
		auto b=permu(v);
		for(int i=0;i<v-1;i++)
			a.emplace_back(b[i],b[i+1]);
		for(int i=0;i+2<v;i+=2)
			a.emplace_back(b[i],b[i+2]);
		return a;
	}
	
	Arr<vector<bool>> enum_ncr(int n,int r){
		vector<bool>a(n);
		for(int i=0;i<r;i++)
			a[n-1-i]=1;
		Arr<vector<bool>> b;
		do{
			b.push_back(a);
		}while(next_permutation(a.begin(),a.end()));
		return b;
	}
	Arr<Arr<int>> enum_npr(int n,int r){
		Arr<Arr<int>> ret;
		for(auto&a:enum_ncr(n,r)){
			Arr<int> b;
			for(int i=0;i<n;i++)
				if(a[i])
					b.push_back(i);
			do{
				ret.push_back(b);
			}while(next_permutation(b.begin(),b.end()));
		}
		return ret;
	}
}
