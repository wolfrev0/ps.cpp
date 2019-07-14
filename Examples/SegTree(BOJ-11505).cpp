#include "Core.h"
#include "Seg.h"
#define endl '\n'//not interactive?
//#define int i64//overflow?

struct A:public Seg<int, 1>{
	A(int n):Seg<int,1>(n){}
	int fq(const int& a, const int& b)override{return i64(a)*b%mod;}
};

signed main(){
	int n,m,k;
	cin>>n>>m>>k;
	A st(n);
	hfor(i,0,n){
		int x;cin>>x;
		st.upd(i,x);
	}
	hfor(i,0,m+k){
		int op,x,y;
		cin>>op>>x>>y;
		if(op==1)
			st.upd(--x,y);
		else
			cout<<st.q(--x,y)<<endl;
	}
	
	return 0;
}