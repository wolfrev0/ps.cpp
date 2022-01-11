#pragma once
#include "core/base.h"

//LeftHull 역추적 방법: 스텝i의 argmin값을 am(i)라고 하자. 스텝n부터 스텝1까지 ans[i]=min(ans[i+1],am(i))하면 된다. 아래는 증명..은 아니고 간략한 이유
//am(i)<=ans[i+1]일때: ans[i]=am(i)
//x[i]>ans[i+1]일때: ans[i]=ans[i+1] 왜냐하면 f(i,a)는 a<x[i]에서 감소함수이므로 가능한 최대로 오른쪽으로 붙은 ans[i+1]이 최적.
//스텝i에서 add_bias(k,0)한다면 간격제한k가 있는것이므로 ans[i]=min(ans[i+1]-k,x[i])으로 수정.
//LR Hull 역추적은 케이스나눠서 위 방법을 확장하면 될듯

//NOTE: f(x)=min{f(x+i),i<a}+|x-k|+m -> pf(k)sf(k)ab(-a,m)
//NOTE: sf_inc에 답구하는게 들어있어서, 반드시 한 연산에 대해 pf_dec->sf_inc순서로 호출
struct LeftHull{
	void pf_dec(int x){pq.push(x-bias);}//x이하의 기울기들 -1
	int sf_inc(int x){//x이상의 기울기들 +1, pop된 원소 반환(Right Hull관리에 사용됨)
		if(pq.empty() or argmin()<=x)return x;
		ans+=argmin()-x;//이 경우 최솟값이 증가함
		pq.push(x-bias);//x 이하 -1
		int r=argmin();pq.pop();//전체 +1
		return r;
	}
	void add_bias(int x,int y){bias+=x;ans+=y;}//그래프 x축 평행이동
	int minval(){return ans;}//최소값
	int argmin(){return pq.empty()?-inf<int>():pq.top()+bias;}//최소값 x좌표
	void operator+=(LeftHull& a){
		ans+=a.ans;
		while(sz(a.pq))pf_dec(a.argmin()), a.pq.pop();
	}
	int size()const{return sz(pq);}
	int pop(){int z=argmin();pq.pop();return z;}
private:
	PQ<int,less<>> pq;
	int ans=0,bias=0;
};

//NOTE: f(x)=min{f(x+i),a<i<b}+|x-k|+m -> pf(k)sf(k)ab(-a,b,m)
struct SlopeTrick{
	void pf_dec(int x){l.pf_dec(-r.sf_inc(-x));}
	void sf_inc(int x){r.pf_dec(-l.sf_inc(x));}
	void add_bias(int lx,int rx,int y){l.add_bias(lx,0),r.add_bias(-rx,0),ans+=y;}
	int minval(){return ans+l.minval()+r.minval();}
	pint argmin(){return {l.argmin(),-r.argmin()};}
	void operator+=(SlopeTrick& a){
		//그냥 Left Right 각각 +=하면 안되는 이유: 최솟값이 증가하며, 최소구간이 꼬일수 있음.
		ans+=a.ans;
		while(sz(a.l))
			pf_dec(a.l.pop());
		l.add_bias(0,a.l.minval());
		while(sz(a.r))
			sf_inc(-a.r.pop());
		r.add_bias(0,a.r.minval());
	}
	int size()const{return l.size()+r.size();}
	
	LeftHull l,r;
	int ans=0;
};

//아직 확실히 검증안됨. codechef문제중에 기울기 큰 업데이트 문제 풀어보자.
struct LeftHullMap{
	void pf_dec(int x,int k){a[x-bias]+=k;}//x이하의 기울기들 -k
	Arr<pint> sf_inc(int x,int k){//x이상의 기울기들 +k, pop된 원소 반환(Right Hull관리에 사용됨)
		Arr<pint> ret;
		while(k and argmin()>x){
			int cnt=min(mincnt(),k);
			ans+=(argmin()-x)*cnt;
			a[x-bias]+=cnt;
			ret.pushb(argmin(),cnt);
			pop(cnt);
			k-=cnt;
		}
		if(k)
			ret.pushb(x,k);
		return ret;
	}
	void add_bias(int x,int y){bias+=x;ans+=y;}//그래프 x축 평행이동
	int minval(){return ans;}//최소값
	int argmin(){return a.empty()?-inf<int>():tail(a)->fi+bias;}//최소값 x좌표
	int mincnt(){return a.empty()?0:a[argmin()-bias];}
	void operator+=(LeftHullMap& a){
		ans+=a.ans;
		while(sz(a.a))
			pf_dec(a.argmin(),a.mincnt()), a.a.erase(tail(a.a));
	}
	int size()const{return sz(a);}
	Arr<pint> pop(int k){
		Arr<pint> ret;
		while(k and sz(a)){
			int c=min(k,tail(a)->se);
			k-=c;
			ret.pushb(argmin(),c);
			if((tail(a)->se-=c)==0)
				a.erase(tail(a));
		}
		return ret;
	}
private:
	map<int,int> a;
	int ans=0,bias=0;
};

struct SlopeTrickMap{
	void pf_dec(int x,int k){
		for(auto [x2,k2]:r.sf_inc(-x,k))
			l.pf_dec(-x2,k2);
	}
	void sf_inc(int x,int k){
		for(auto [x2,k2]:l.sf_inc(x,k))
			r.pf_dec(-x2,k2);
	}
	void add_bias(int lx,int rx,int y){l.add_bias(lx,0),r.add_bias(-rx,0),ans+=y;}
	int minval(){return ans+l.minval()+r.minval();}
	pint argmin(){return {l.argmin(),-r.argmin()};}
	void operator+=(SlopeTrickMap& a){
		//그냥 Left Right 각각 +=하면 안되는 이유: 최솟값이 증가하며, 최소구간이 꼬일수 있음.
		ans+=a.ans;
		for(auto [x,k]:a.l.pop(inf<int>()))
			pf_dec(x,k);
		l.add_bias(0,a.l.minval());
		for(auto [x,k]:a.r.pop(inf<int>()))
			sf_inc(-x,k);
		r.add_bias(0,a.r.minval());
	}
	int size()const{return l.size()+r.size();}
	
	LeftHullMap l,r;
	int ans=0;
};

//Direct한 기울기 저장
struct SlopeTrick1der{
	//min(f(a),f(a-1)+x)
	void add(int x){pq.push(x);}
	PQ<int,less<int>> pq;
	//TODO
};