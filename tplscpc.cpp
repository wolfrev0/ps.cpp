#include "Core.h"
#include "FastIO.h"
#include "PrettyIO.h"
//#include "PrettyDebug.h"

#if !(INTERACTIVE)
	#define endl '\n'
#endif
using pint = pair<int,int>;
using tint = tuple<int,int,int>;

signed main(){
	int t; cin>>t;
	cfor(ti,1,t){
		cout<<"Case #"<<ti<<endl;
	}
}
