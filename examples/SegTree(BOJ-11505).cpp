#include "Core.h"
#include "Seg.h"
#define endl '\n'//not interactive?
//#define int i64//overflow?

using T=int;
struct F{
	static T id(){return 1;}
	static T q(const T& a, const T& b){return i64(a)*b%mod;}
};

signed main(){
	int n,m,k;
	cin>>n>>m>>k;
	Seg<T, F> st(n);
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