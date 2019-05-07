#pragma once
#include "Core.h"

vector<vector<i64>> knuth_opt(const vector<i64>& init, const function<i64(int,int)>& c){
	int n=init.size();
	vector<vector<i64>> dp(n+1,vector<i64>(n+1));
	vector<vector<int>> a(n,vector<int>(n+1));
	forh(i, 0, n)
		a[i][i+1]=i;
	forc(d, 2, n){
		forc(i, 0, n-d){
			dp[i][i+d]=inf<i64>();
			forc(k, a[i][i+d-1], a[i+1][i+d]){
				if(dp[i][k+1] + dp[k+1][i+d]+c(i,i+d) < dp[i][i+d]){
					dp[i][i+d]=dp[i][k+1] + dp[k+1][i+d]+c(i,i+d);
					a[i][i+d]=k;
				}
			}
		}
	}
	return dp;
}

//max should be (tan,yic)-increase order
//min should be (tan,yic)-decrease order
//d[i] = min{j<i, a[j]*b[i]+c[j]}+e[i]
//min, max, j<i, i<j<n 모두 가능하다. 그림을 잘 생각해서 써라.
//정밀도가 문제가 된다면 x좌표 말고 ccw로 처리하는 방법도 있다. 아래링크 참고
//https://cp-algorithms.com/geometry/convex_hull_trick.html
struct Line{
	i64 tan;
	mutable i64 yic;
	mutable f64 lx=-1/0.0, rx=1/0.0;

	bool operator<(const Line& r)const{return tan<r.tan;}
	bool operator<(const i64 x)const{return rx<x;}

	f64 intersectX(const Line& r)const{return (r.yic-yic)/f64(tan-r.tan);} 
	i64 f(i64 x)const{return tan*x+yic;}
};

struct CHTStack{
	vector<Line> st;
	
	void push(i64 tan, i64 yic){
		Line f{tan, yic, 0};
		while(st.size()){
			f.lx=st.back().intersectX(f);
			if(tan==st.back().tan || f.lx<st.back().lx)
				st.pop_back();
			else
				break;
		}
		st.push_back(f);
	}

	i64 get(i64 x){
		int s=0, e=st.size();
		while(e-s>1){
			int m=(s+e)/2;
			(x<st[m].lx?e:s)=m;
		}
		return st[s].tan*x + st[s].yic;
	}
};

struct DynCHT{
	void insert(i64 a, i64 b){
		auto it=s.find({a, b});
		if(it!=s.end())
			b=max(b, it->yic), s.erase(it);
		Line f={a,b};

		auto r=s.upper_bound({a,b});
		while(r!=s.end() && f.intersectX(*r)>r->rx)
			r=s.erase(r);
		auto l=mri(s.lower_bound({a,b}));
		while(l!=s.rend() && f.intersectX(*l)<l->lx)
			l=rerase(s, l);
		
		if(r!=s.end())
			f.rx=r->lx=f.intersectX(*r);
		if(l!=s.rend())
			f.lx=l->rx=f.intersectX(*l);
		s.insert(f);
	}

	i64 query(i64 x){
		auto it=s.lower_bound(x);
		return it->tan*x+it->yic;
	}
private:
	set<Line, less<>> s;
};