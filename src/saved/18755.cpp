#include "core/base.h"

#define endl '\n' // Remove it when interactive
#define CHECK_INPUT 1
#define TC get<0>(input()) //1
#define TC_OUT_PREFIX ""//"Case #",ti,": "
signed main(){
	void solve();
	for(int ti=1,t=TC;ti<=t;ti++)
		print(TC_OUT_PREFIX),
		solve();
#if CHECK_INPUT
	assert(cin.get()=='\n');
	assert(cin.get()==EOF);
#endif
}

int k;
struct Hull{
	int sum=0;
	PQ<int,greater<int>> sl;//slopes, idx = sz(sl)-1 to 0
	void minkowski_sum(Hull&& r){
		sum+=r.sum;
		while(sz(r.sl))
			sl.push(r.sl.top()),r.sl.pop();
		while(sl.size()>k)
			sum-=sl.top(),sl.pop();
	}
	//add a*min(i,b-i) to graph
	void update(int a, int b){
		int zsum=0;
		PQ<int,greater<int>> z;
		while(sz(sl)){
			int x=sl.top();sl.pop();
			int idx=sz(sl);
			int val;
			if(idx*2<b)
				val=(idx+1)*2<=b?x+a:x;
			else
				val=x-a;
			z.push(val);
			zsum+=val;
		}
		swap(z,sl);
		swap(zsum,sum);

		while(sz(sl)>k)
			sum-=sl.top(),sl.pop();
	}
	int get(){
		return sum;
	}
	void dbgstatus(){
		dbgprint("slopes: ");
		auto z=sl;
		Arr<int> a;
		while(sz(z))
			a.push_back(z.top()),z.pop();
		reverse(a.begin(),a.end());
		for(auto i:a)
			dbgprint(i,' ');
		dbgprintln("");
		dbgprint("values: ");
		int y=0;
		dbgprint(y,' ');
		for(auto i:a)
			dbgprint(y+=i,' ');
		dbgprintln("");
		dbgprintln("sum: ",sum);
	}
};

void solve(){
	auto[n,k]=input<int,2>();
	::k=k;
	Arr<Arr<pint>> g(n);
	for(int i=0;i<n-1;i++){
		auto[u,v,w]=input<int,3>();
		u--,v--;
		g[u].emplace_back(v,w);
		g[v].emplace_back(u,w);
	}
	int ans=0;
	func(Hull,dfs,int x,int p){
		Hull a;
		a.sl.push(0);
		sort(g[x].begin(),g[x].end(),val2cmp([&](pint i){return -sz(g[i.first]);}));
		for(auto [y,w]:g[x]){
			if(y!=p){
				auto b=dfs(y,x);
				dbgprintln("status of ",x,' ',y);
				b.dbgstatus();
				b.update(2*w,k);
				b.dbgstatus();
				if(sz(a.sl) > sz(b.sl))
					a.minkowski_sum(move(b));
				else{
					b.minkowski_sum(move(a));
					swap(a,b);
				}
			}
		}
		dbgprintln("status of ",x);
		a.dbgstatus();
		dbgprintln("=======================");
		ans=max(ans,a.get());
		return a;
	};
	dfs(0,0);
	println(ans);
}
