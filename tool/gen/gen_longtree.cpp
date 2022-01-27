#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
 
//TODO:성게모양
signed main(signed argc, char* argv[]){
	registerGen(argc, argv, 1);
	int n=stoi(argv[1]),k=stoi(argv[2]);
	vector<vector<vector<int>>> forest;
	for(int i=0;i<n;i++){
		int m=stoi(argv[3]);
 
		forest.push_back({});
		auto&g=forest.back();
		g=vector<vector<int>>(m);
 
		auto add_edge=[&g](int x,int y){
			g[x].push_back(y);
			g[y].push_back(x);
		};
 
		int z=0;
		while(z<m){
			int y=rnd.next(1,m-z);
			for(int j=1;j<y;j++)
				add_edge(z+j-1,z+j);
			if(z)
				add_edge(rnd.next(0,z-1),z);
			z+=y;
		}
	}
	cout<<n<<' '<<k<<endl;
	for(int i=0;i<n;i++){
		int m=forest[i].size();
		cout<<m<<endl;
		for(int x=0;x<m;x++)
			for(auto y:forest[i][x])
				if(x<y)
					cout<<x+1<<' '<<y+1<<endl;
	}
}
