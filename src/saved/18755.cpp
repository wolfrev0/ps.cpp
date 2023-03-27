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
	vector<int> sl;//slopes
	void minkowski_sum(Hull&& r){
		sum+=r.sum;
		sl.insert(sl.end(),r.sl.begin(),r.sl.end());

		sort(sl.begin(),sl.end());
		reverse(sl.begin(),sl.end());
		while(sl.size()>k)
			sum-=sl.back(),sl.pop_back();
	}
	//add a*min(i,b-i) to graph
	void update(int a, int b){
		int i=0;
		vector<int> z;
		for(auto& x:sl){
			if(i*2<b)
				z.push_back((i+1)*2<=b?x+a:x);
			else
				z.push_back(x-a);
			i++;
		}
		swap(z,sl);

		sum=reduce(sl.begin(),sl.end());
		sort(sl.begin(),sl.end());
		reverse(sl.begin(),sl.end());
		while(sl.size()>k)
			sum-=sl.back(),sl.pop_back();
	}
	int get(){
		return sum;
	}
	void dbgstatus(){
		dbgprint("slopes: ");
		for(auto i:sl)
			dbgprint(i,' ');
		dbgprintln("");
		dbgprint("values: ");
		int y=0;
		dbgprint(y,' ');
		for(auto i:sl)
			dbgprint(y+=i,' ');
		dbgprintln("");
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
		a.sl.push_back(0);
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
