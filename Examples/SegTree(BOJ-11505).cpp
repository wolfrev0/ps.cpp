#include "Core.h"
#include "Seg.h"
#define endl '\n'//do not use when solving interactive problem!!!

struct A{
	i64 a;
	A(i64 a=1):a(a){}
	bool operator==(const A& r)const{return a==r.a;}
};
struct B{
	i64 a;
	B(i64 a=987654321):a(a){}
	bool operator==(const B& r)const{return a==r.a;}
};

struct Func{
	static A q(A a, A b){return a.a*b.a%mod;};
	static A upd(A a, B b){return b.a;};
};

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(11);
	srand((unsigned)time(0));
	
	int n, m, k;
	cin>>n>>m>>k;
	Seg<A, B, Func> st(n);
	forh(i,0,n){
		i64 x;
		cin>>x;
		st.update(i,x);
	}
	forh(i, 0, m+k){
		int a;
		cin>>a;
		if(a==1){
			int b;
			i64 c;
			cin>>b>>c;
			b--;
			st.update(b, c);
		}else{
			int b, c;
			cin>>b>>c;
			b--, c--;
			cout<<st.query(b, c+1).a<<endl;
		}
	}

	return 0;
}