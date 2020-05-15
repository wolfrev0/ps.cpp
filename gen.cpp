#include "Core.h"

#define endl '\n'//not interactive?
#define int i64//MLE?
using pint = pair<int,int>;
using tint = tuple<int,int,int>;

signed main(){
	int n=1000000/300; cout<<n<<endl;
	rep(i,n){
		rep(j,300)
			cout<<'a';
		cout<<endl;
	}
	rep(i,200000)
		cout<<'a';
	cout<<endl;
	
	return 0;
}

