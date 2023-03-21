#include "core/base.h"
#include "misc/gccext.h"

struct Hull{
	int zp=0;
	pbds_pq<int> pq;//slopes
	void minkowski_sum(Hull&& r){
		zp+=r.zp;
		pq.join(r.pq);
	}
	//add a*min(i,b-i) to graph
	void update(int a, int b){
		zp+=0; //a*b should be even
		int i=0;
		pbds_pq<int> z;
		for(auto& x:pq){
			if(i*2<b)
				z.push((i+1)*2<=b?x:x+a);
			else
				z.push(x-a);
			i++;
		}
		swap(z,pq);
	}
	int get(){
		int ret=zp;
		int acc=0;
		for(auto i:pq){
			acc+=i;
			ret=max(ret,ret+acc);
		}
		return ret;
	}
};

void solve(){
	auto[n,k]=input<int,2>();
	Arr<Arr<pint>> g(n);
	for(int i=0;i<n-1;i++){
		auto[u,v,w]=input<int,3>();
		u--,v--;
		g[u].emplace_back(v,w);
		g[v].emplace_back(u,w);
	}
	func(Hull,dfs,int x,int p){
		Hull a;
		a.pq.push(0);
		for(auto [y,w]:g[x]){
			if(y!=p){
				auto b=dfs(y,x);
				b.update(2*w,k);
				a.minkowski_sum(move(b));
			}
		}
		return a;
	};
	cout<<dfs(0,0).get()<<endl;
}
