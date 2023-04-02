#pragma once
#include "geom/line.h"
#include "misc/i128.h"

//NOTE:골치아프면 걍 리차오 쓰자

//max(lower convex envelope),increasing tangent
//3x3 determinant로 교점안구하고 cht가능
//https://www.geeksforgeeks.org/check-three-straight-lines-concurrent-not/
//point-line duality로 y=ax+b==(a,-b)형태 변환하고 ccw사용하는것도 가능
template<class T>
struct CHTint{
	Arr<pair<Line<T>,T>> stk;//pair<직선,추가정보>
	i128 det(Line<T> x,Line<T> y,Line<T> z){return (i128)x.a*y.b*z.c+(i128)x.b*y.c*z.a+(i128)x.c*y.a*z.b-(i128)x.c*y.b*z.a-(i128)x.b*y.a*z.c-(i128)x.a*y.c*z.b;}
	void push(Line<T> a,T v){
		while(sz(stk)>=2 and det(stk[-2].fi,stk[-1].fi,a)>=0)
			stk.popb();
		if(sz(stk)and stk.back().fi.tan()==a.tan()){
			if(stk.back().fi.calcY(0)<a.calcY(0))
				stk.back()={a,v};
			return;
		}
		stk.push_back(a,v);
	}
	int i=0;
	pair<pint,T> q(int x){
		while(i+1<sz(stk)){
			if(x<stk[i].fi.intersect(stk[i+1].fi).x)
				break;
			i++;
		};
		return{stk[i].fi.calY(x),stk[i].se};
	}
};

auto mri(auto it){return make_reverse_iterator(it);}//*mri(it)==*prev(it)
auto rerase(auto& c,auto ri){return mri(c.erase(prev(ri.base())));}

using T=fp;
struct L{
	T tan,yic;
	mutable fp lx=-1/0.0,rx=1/0.0;
	bool operator<(const L& r)const{return tan<r.tan;}
	bool operator<(const T x)const{return rx<x;}
	fp cpx(const L& r)const{return (r.yic-yic)/fp(tan-r.tan);}
	T f(T x)const{return tan*x+yic;}
};

// max(lower convex envelope),increasing tangent
// Note:
// 점화식형태 d[i]=min{j<i}(a[j]*b[i]+c[j])+e[i]
// b[i]를 x,a[j]를 기울기로 생각하면 그려진다.
// min,max,j<i,i<j<n 모두 식정리해주면 가능하다.
struct CHTStk{
	Arr<L> st;
	void add(T tan,T yic){
		L z{tan,yic,0};
		while(sz(st)){
			z.lx=st.back().cpx(z);
			if(tan==st.back().tan or z.lx<st.back().lx) st.pop_back();
			else break;
		}
		st.push_back(z);
	}
	T q(T x){
		int s=0,e=sz(st);
		while(e-s>1){
			int m=(s+e)/2;
			(x<st[m].lx?e:s)=m;
		}
		return st[s].tan*x+st[s].yic;
	}
	//amortized O(1), x값 단조증가시 사용가능
	int s=0;
	T q2(T x){
		while(s<sz(st)and x >= st[s].lx)s++;
		return st[s-1].tan*x+st[s-1].yic;
	}
};

// max(lower convex envelope)
struct CHTSet{
	void add(T a,T b){
		auto it=s.find({a,b});
		if(it!=s.end())b=max(b,it->yic),s.erase(it);

		L z={a,b};
		auto r=s.ub(z);
		while(r!=s.end()&& z.cpx(*r)>= r->rx)r=s.erase(r);
		auto l=mri(s.lb(z));
		while(l!=s.rend()&& z.cpx(*l)<= l->lx)l=rerase(s,l);

		z.rx=r!=s.end()? z.cpx(*r): 1/0.;
		z.lx=l!=s.rend()? z.cpx(*l): -1/0.;
		if(z.lx>z.rx)return;
		s.insert(z);
		if(r!=s.end())r->lx=z.rx;
		if(l!=s.rend())l->rx=z.lx;
	}

	T q(T x){
		auto it=s.lb(x);
		return it->tan*x+it->yic;
	}
private:
	set<L,less<>> s;
};
