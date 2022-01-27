#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

signed main(signed argc, char* argv[]){
	registerGen(argc, argv, 1);
	
	int n=stoi(argv[1]),m=stoi(argv[2]);
	
	set<pair<int,int>> g;

	for(int i=2;i<=n;i++)
		g.insert({rnd.next(1,i-1),i});

	if(n<=5000){
		vector<pair<int,int>> a;
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
				if(!g.count({i,j}))
					a.push_back({i,j});
		for(int i=0;i<a.size();i++)
			swap(a[i],a[rnd.next(0,i)]);
		for(int i=0;g.size()<m;i++)
			g.insert(a[i]);
	}else{
		while(g.size()<m){
			int u=rnd.next(1,n),v=rnd.next(1,n);
			if(u==v)continue;
			if(u>v)swap(u,v);
			g.insert({u,v});
		}
	}
	ensure(g.size()==m);

	cout<<n<<' '<<m<<endl;
	for(auto [u,v]:g){
		if(rnd.next(0,1))swap(u,v);
		cout<<u<<' '<<v<<' '<<rnd.next(1,10000)<<endl;
	}
	for(int i=0;i<n-1;i++)
		cout<<rnd.next(0,10000)<<' ';
	cout<<rnd.next(0,10000)<<endl;
}
