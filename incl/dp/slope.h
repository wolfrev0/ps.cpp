#pragma once
#include "core/base.h"

//NOTE: 점화식 형태 f(i,x) = min(f(i-1,y))+(slopetrickable) 형태에 적용가능
//Fireworks는 점화식 형태가 다르기 때문에 적용불가능
//NOTE: Concave의 LeftHull을 관리하며, 최솟값이 ans에 저장됨
//NOTE: 모든 slope-trickable 함수는 pf_dec과 sf_inc의 조합으로 만들 수 있는듯? 단, y=abs(x-k)+m 같은건 최솟값이 m이라서 수동으로 ans+=m해줘야 함
//NOTE: sf_inc에 답구하는게 들어있어서, 반드시 한 연산에 대해 pf_dec->sf_inc순서로 호출해야함 (https://atcoder.jp/contests/arc123/tasks/arc123_d)
//https://codeforces.com/contest/713/my
struct HalfHull{
	void pf_dec(int x){pq.empl(x-bias);}//x이하의 기울기들 -1
	void sf_inc(int x){//x이상의 기울기들 +1
		if(sz(pq) and pq.top()+bias>x){
			ans+=(pq.top()+bias)-x;//이 경우 최솟값이 증가함
			pq.empl(x-bias);//x 이하 -1
			pq.pop();//전체 +1
			//결과적으로 x이상만 +1됨
		}
	}
	void add_bias(int x){bias+=x;}//그래프 x축 평행이동
	PQMax<int> pq;
	int ans=0,bias=0;
};
//역추적 방법: 각 스텝별로 pq.top()+bias가 해당스텝에서 최소x좌표임. 스텝i의 해당값을 sav[i]라고 하자.
//이제 스텝n부터 스텝1까지 ans[i]=min(ans[i+1],sav[i])하면 된다. 아래는 증명..은 아니고 간략한 이유
//sav[i]<=ans[i+1]일때: ans[i]=sav[i]
//sav[i]>ans[i+1]일때: ans[i]=ans[i+1] 왜냐하면 f(i,x)는 x<sav[i]에서 감소함수이므로 가능한 최대로 오른쪽으로 붙은 ans[i+1]이 최적
//NOTE: 단계 i에서 add_bias(k)한다면 간격제한k가 있는것이므로 역추적은 ans[i]=min(ans[i+1]-k,sav[i])이다.

struct SlopeTrick{
	HalfHull l,r;
	void pf_dec(int x){
		l.pf_dec(x);
		r.pf_dec(-x);
	}
	void sf_inc(int x){
		l.sf_inc(x);
		r.sf_inc(-x);
	}
	void add_bias(int x){l.bias+=x;r.bias-=x;}
};