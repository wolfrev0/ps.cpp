#include "Core.h"
#include "FastIO.h"
template<typename T>ostream& operator<<(ostream& s, const Arr<T>& a) {for(auto i:a) cout<<i<<' '; return s;}
auto cinint(){i64 x;cin>>x;return x;}
auto cinchr(){char x;cin>>x;return x;}
auto cinints(int n){Arr<i64> a(n);for(auto&i:a)cin>>i;return a;}

//#define endl '\n'//Interactive? Partial Score?
#define int i64//MLE?
using pint = pair<int,int>;
using tint = tuple<int,int,int>;

signed main(){
	int t; cin>>t;
	cfor(ti,1,t){
		cout<<"Case #"<<ti<<endl;
	}
}
