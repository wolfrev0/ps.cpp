#pragma once
#include "Core.h"

auto mri(auto it){ return make_reverse_iterator(it); }//*mri(it) == *prev(it) 
auto rerase(auto& c, auto ri){ return mri(c.erase(prev(ri.base()))); } 

//Formula:
//d[i] = min{j<i, a[j]*b[i]+c[j]}+e[i]
//Constraints:(StackCHT Only)
//max should be (tan,yic)-increase order
//min should be (tan,yic)-decrease order
//Note:
//b[i]를 x, a[j]를 기울기로 생각하면 그려진다.
//min, max, j<i, i<j<n 모두 가능하다. 그림을 잘 생각해서 써라.
//정밀도가 문제가 된다면 x좌표 말고 ccw로 처리하는 방법도 있다. 아래링크 참고
//https://cp-algorithms.com/geometry/convex_hull_trick.html
//Line은 Line.h와 중복이니 상속받아서 잘 변형하는 식으로 개선해보자.
struct Line{
	i64 tan, yic;
	mutable f64 lx=-1/0.0, rx=1/0.0;

	bool operator<(const Line& r)const{return tan<r.tan;}
	bool operator<(const i64 x)const{return rx<x;}

	f64 cpx(const Line& r)const{return (r.yic-yic)/f64(tan-r.tan);} 
	i64 f(i64 x)const{return tan*x+yic;}
};
struct CHTStack{
	Arr<Line> st;
	
	void push(i64 tan, i64 yic){
		Line z{tan, yic, 0};
		while(sz(st)){
			z.lx=st.back().cpx(z);
			if(tan==st.back().tan || z.lx<st.back().lx)
				st.popb();
			else
				break;
		}
		st.pushb(z);
	}

	i64 q(i64 x){
		int s=0, e=sz(st);
		while(e-s>1){
			int m=(s+e)/2;
			(x<st[m].lx?e:s)=m;
		}
		return st[s].tan*x + st[s].yic;
	}
};

//max
struct DynCHT{
	void add(i64 a, i64 b){
		auto it=s.find({a, b});
		if(it!=s.end())
			b=max(b, it->yic), s.erase(it);
		
		Line z={a,b};
		auto r=s.upper_bound(z);
		while(r!=s.end() && z.cpx(*r)>=r->rx)
			r=s.erase(r);
		auto l=mri(s.lower_bound(z));
		while(l!=s.rend() && z.cpx(*l)<=l->lx)
			l=rerase(s, l);
		
		z.rx = r!=s.end()?z.cpx(*r):1/0.;
		z.lx = l!=s.rend()?z.cpx(*l):-1/0.;
		if(z.lx>z.rx)
			return;
		s.insert(z);
		if(r!=s.end()) r->lx=z.rx;
		if(l!=s.rend()) l->rx=z.lx;
	}

	i64 q(i64 x){
		auto it=s.lower_bound(x);
		return it->tan*x+it->yic;
	}
private:
	set<Line, less<>> s;
};

//Formula:
//연쇄행렬곱꼴인데 formal한 표현이 뭐더라?
//Constraints:
//사각부등식? 뭐더라 W[a][b]+W[c][d]<=W[a][d]+W[b][c]인가?
//Note:
Arr<Arr<i64>> knuth_opt(const Arr<i64>& init, const function<i64(int,int)>& c){
	int n=sz(init);
	Arr<Arr<i64>> dp(n+1,Arr<i64>(n+1));
	Arr<Arr<int>> a(n,Arr<int>(n+1));
	hfor(i, 0, n)
		a[i][i+1]=i;
	cfor(d, 2, n){
		cfor(i, 0, n-d){
			dp[i][i+d]=inf<i64>();
			cfor(k, a[i][i+d-1], a[i+1][i+d]){
				if(dp[i][k+1] + dp[k+1][i+d]+c(i,i+d) < dp[i][i+d]){
					dp[i][i+d]=dp[i][k+1] + dp[k+1][i+d]+c(i,i+d);
					a[i][i+d]=k;
				}
			}
		}
	}
	return dp;
}

//Formula:
//cht랑 비슷했던거같은데...
//Constraints:
//사각부등식? 뭐더라 W[a][b]+W[c][d]<=W[a][d]+W[b][c]인가?
//Note:
void dnc_opt(){}