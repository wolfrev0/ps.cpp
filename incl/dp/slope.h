#pragma once
#include "core/base.h"

//NOTE: f(x)=min{f(x+i),i<a}+|x-k|+m -> pf(k)sf(k)ab(-a,m)
//NOTE: sf_inc에 답구하는게 들어있어서, 반드시 한 연산에 대해 pf_dec->sf_inc순서로 호출
struct LeftHull{
	void pf_dec(int x){pq.empl(x-bias);}//x이하의 기울기들 -1
	int sf_inc(int x){//x이상의 기울기들 +1, pop된 원소 반환(Right Hull관리에 사용됨)
		if(sz(pq) and argmin()>x){
			ans+=argmin()-x;//이 경우 최솟값이 증가함
			pq.empl(x-bias);//x 이하 -1
			int r=argmin();pq.pop();//전체 +1
			return r;
		}
		return x;
	}
	void add_bias(int x,int y){bias+=x;ans+=y;}//그래프 x축 평행이동
	int getmin(){return ans;}//최소값
	int argmin(){return pq.empty()?-inf<int>():pq.top()+bias;}//최소값 x좌표
private:
	PQMax<int> pq;
	int ans=0,bias=0;
};

//NOTE: f(x)=min{f(x+i),a<i<b}+|x-k|+m -> pf(k)sf(k)ab(-a,b,m)
struct SlopeTrick{
	void pf_dec(int x){l.pf_dec(-r.sf_inc(-x));}
	void sf_inc(int x){r.pf_dec(-l.sf_inc(x));}
	void add_bias(int lx,int rx,int y){l.add_bias(lx,0),r.add_bias(-rx,0),ans+=y;}
	int getmin(){return ans+l.getmin()+r.getmin();}
	pint argmin(){return {l.argmin(),-r.argmin()};}
private:
	LeftHull l,r;
	int ans=0;
};

//LeftHull 역추적 방법: 스텝i의 argmin값을 am(i)라고 하자. 스텝n부터 스텝1까지 ans[i]=min(ans[i+1],am(i))하면 된다. 아래는 증명..은 아니고 간략한 이유
//am(i)<=ans[i+1]일때: ans[i]=am(i)
//x[i]>ans[i+1]일때: ans[i]=ans[i+1] 왜냐하면 f(i,a)는 a<x[i]에서 감소함수이므로 가능한 최대로 오른쪽으로 붙은 ans[i+1]이 최적.
//스텝i에서 add_bias(k,0)한다면 간격제한k가 있는것이므로 ans[i]=min(ans[i+1]-k,x[i])으로 수정.
//LR Hull 역추적은 케이스나눠서 위 방법을 확장하면 될듯