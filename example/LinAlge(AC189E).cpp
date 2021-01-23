#include "Core.h"
#include "FastIO.h"
#include "PrettyIO.h"
#include "PrettyDebug.h"
#include "LinAlge.h"

Mat<int> mvmat(int x, int y){ return Mat<int>(3,3,{1,0,x, 0,1,y, 0,0,1}); }

signed main(){
	Mat<int> rc(3,3,{0,1,0, -1,0,0, 0,0,1});
	Mat<int> rcc(3,3,{0,-1,0, 1,0,0, 0,0,1});
	Mat<int> fx(3,3,{-1,0,0, 0,1,0, 0,0,1});
	Mat<int> fy(3,3,{1,0,0, 0,-1,0, 0,0,1});
	
	int n; cin>>n;
	Arr<pint> a(n);
	for(auto& [x,y]:a)cin>>x>>y;

	int m; cin>>m;
	Arr<pint> op(m);
	for(auto& [x,y]:op){ cin>>x; if(x>2)cin>>y; }

	int q; cin>>q;
	map<int,Arr<pint>> qa;
	for(int i=0;i<q;i++){
		CIN(int,x,y); y--;
		qa[x].emplb(y,i);
	}

	Mat<int> z(3,3,true);
	Arr<pint> ans(q);
	for(int i=0;i<=m;i++){
		for(auto [j,k]:qa[i]){
			auto w=z*Mat<int>(3,1,{a[j].fi,a[j].se,1});
			ans[k]={w.a[0][0],w.a[1][0]};
		}
		if(op[i].fi==1) z=rc*z;
		else if(op[i].fi==2) z=rcc*z;
		else if(op[i].fi==3) z= mvmat(op[i].se,0)*fx*mvmat(-op[i].se,0)*z;
		else if(op[i].fi==4) z= mvmat(0,op[i].se)*fy*mvmat(0,-op[i].se)*z;
	}
	for(auto [x,y]:ans)
		cout<<x<<' '<<y<<endl;
}
