#include "Core.h"
#include "SegTree.h"
#define endl '\n'//do not use when solving interactive problem!!!

struct Func{
	static i64 idT(){return 1;}
	static i64 idU(){return 987654321;}
	static i64 q(i64 a, i64 b){return a*b%mod;};
	static i64 upd(i64 a, i64 b, int cnt){return b;};
	static i64 propa(i64 a, i64 b){return b;}
};

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(11);
	srand((u32)time(0));
	
	int n, m, k;
	cin>>n>>m>>k;
	SegTree<i64, i64, Func> st(n);
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
			st.update(b, b+1, c);
		}else{
			int b, c;
			cin>>b>>c;
			b--, c--;
			cout<<st.query(b, c+1)<<endl;
		}
	}

	return 0;
}
