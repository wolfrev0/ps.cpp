#include "core/base.h"
signed main(){
	void solve();
	// for(int ti=1,t=input1();ti<=t;ti++)
		// print("Case #",ti,": "),
		solve();
	// assert(cin.get()==' ');
	// assert(cin.get()=='\n');
	// assert(cin.get()==EOF);
}
#include "misc/random.h"
const int N=2,X=7;
// const int N=4,X=30;
// const int N=10,X=8;
void solve(){
	int t=1;
	println(t);
	while(t--){
		int n=N;
		println(n);
		while(n--){
			int x=0,y=0;
			while(x+y==0)
				x=rd(X),y=rd(X);
			println(x,' ',y);
		}
	}
}
