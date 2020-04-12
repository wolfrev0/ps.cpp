#include "Core.h"
#define endl '\n'//not interactive?
#define int i64//MLE?
using pint = pair<int,int>;
using tint = tuple<int,int,int>;

void f(int n){
	int x=999999;
	defer(cout<<x<<endl;);
	if(!n) return;
	x=n*n;
	f(n-1);
}

signed main(){
	f(5);
	return 0;
}

