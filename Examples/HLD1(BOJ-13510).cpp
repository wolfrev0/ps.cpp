#include "Core.h"
#include "HLD.h"
#define endl '\n'//do not use when solving interactive problem!!!

struct F{
	static int idT(){return 0;}
	static int idU(){return 0;}
	static int q(const int& a, const int& b){return max(a,b);}
	static int upd(const int& a, const int& b, int c){return b;}
	static int propa(const int& a, const int& b){return b;}
};

struct Solver:public HLD<int, int, F>{
	Solver(const Tree<int>&t, int r):HLD<int,int,F>(t,r){}

	using HLD<int,int,F>::parent;
	using HLD<int,int,F>::update;
	void update(int u, int v, int c){
		if(parent[v].e==u)
			swap(u, v);
		update(u, c);
	}
};

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(11);
	srand((u32)time(0));
	
	int n;
	cin>>n;
	pair<int,int> e[100000];
	Tree<int> t(n);
	forh(i, 0, n-1){
		int a, b, c;
		cin>>a>>b>>c;
		a--, b--;
		t.add_edge(a,b,c);
		e[i]={a,b};
	}
	Solver s(t, 0);
	int m;
	cin>>m;
	forh(i, 0, m){
		int a, b, c;
		cin>>a>>b>>c;
		if(a==1){
			b--;
			s.update(e[b].first, e[b].second, c);
		}else{
			b--, c--;
			cout<<s.query(b, c)<<endl;
		}
	}

	return 0;
}