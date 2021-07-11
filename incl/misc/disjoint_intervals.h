//Kick Start 2021 Round D Problem C: Final Exam

#include "core/base.h"

//Don't use it at interactive
#include "core/fastio.h"
#define endl '\n'

struct A{
	int l,r;
	bool operator<(const A& x)const{return l<x.l;}
	int dist(int x)const{return l<=x and x<=r?0:min(abs(x-r),abs(x-l));}
	Arr<A> split(int x,int& ans){
		if(l==r){ans=l;return {};}
		if(x<=l){ans=l;return {A{l+1,r}};}
		if(x>=r){ans=r;return {A{l,r-1}};}
		ans=x; return {A{l,x-1},A{x+1,r}};
	}
};

void solve(){
	READ(int,n,m);
	set<A> a;
	for(int i=0;i<n;i++){
		READ(int,l,r);a.empl(A{l,r});
	}
	for(int i=0;i<m;i++){
		int x=cin.tok();
		auto it=a.lb({x,0});
		
		A z;
		if(it==a.end()) z=*prev(it);
		else if(it==a.begin()) z=*it;
		else z=prev(it)->dist(x)<=it->dist(x)?*prev(it):*it;
		a.erase(z);
		
		int ans;
		for(auto i:z.split(x,ans))
			a.insert(i);
		cout<<ans<<' ';
	}
	cout<<endl;
}
signed main(){
	int ti=0,t=cin.tok();
	while(++ti<=t)
		cout<<"Case #"<<ti<<": ",
		solve();
}