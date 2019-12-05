#include "Core.h"
#include "HLD.h"
#define endl '\n'//do not use when solving interactive problem!!!

struct A{
	bool b=false;
	int n=-1;
	A operator+(const A& r)const{
		if(r.b && n==-1)
			return r;
		return *this;
	}
	bool operator==(const A&r)const{return b==r.b && n==r.n;}
};

struct B{
	bool b=false;
	int n=-2;
	B(bool b, int n):b(b), n(n){}
	B(A a):b(a.b), n(a.n){}
	operator A()const{return {b,n};}
	bool operator==(const B&r)const{return b==r.b && n==r.n;}
};

struct F{
	static A q(const A& a, const A& b){return a+b;}
	static A upd(const A& a, const B& b){return b;}
	static B propa(const B& a, const B& b){return b;}
};

struct Solver:public HLD<A,B,F>{
	Solver(const Tree<A>&t, int r):HLD<A,B,F>(t,r){}

	using HLD<A,B,F>::parent;
	using HLD<A,B,F>::update;
	using HLD<A,B,F>::query;

	void update(int v){
		update(v, B(!parent[v].w.b, !parent[v].w.b?v:-1));
		parent[v].w.b=!parent[v].w.b;
	}

	A query(int v){return query(0, v, false);}
};

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(11);
	srand((unsigned)time(0));
	
	int n;
	cin>>n;
	Tree<A> t(n);
	forh(i, 0, n-1){
		int a, b;
		cin>>a>>b;
		a--, b--;
		t.add_edge(a,b,A());
	}
	Solver s(t, 0);
	int m;
	cin>>m;
	forh(i, 0, m){
		int a, b;
		cin>>a>>b;
		if(a==1)
			s.update(b-1);
		else{
			auto ans = s.query(b-1).n;
			cout<<(ans<0?ans:ans+1)<<endl;
		}
	}

	return 0;
}
