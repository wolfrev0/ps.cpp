#pragma once
#include "core/base.h"

//NOTE: Concave의 LeftHull을 관리하며, 최솟값이 ans에 저장됨
//NOTE: y=abs(x-k)+k 같이 괴상한 함수는 최솟값이 k라서 수동으로 ans+=k해줘야 함
//NOTE: 모든 slope-trickable 함수는 pf_dec과 sf_inc의 조합으로 만들 수 있는듯(내 추측임)
//NOTE: sf_inc에 답구하는게 들어있어서, 반드시 한 연산에 대해 pf_def->sf_inc순서로 호출해야함(https://atcoder.jp/contests/arc123/tasks/arc123_d)
//https://codeforces.com/contest/713/my
struct SlopeTrick{
	void pf_dec(int x){pq.empl(x-bias);}//x이하의 기울기들 -1
	void sf_inc(int x){//x이상의 기울기들 +1
		if(sz(pq) and pq.top()+bias>x){
			ans+=(pq.top()+bias)-x;//최솟값이 올라감
			pq.pop();//1) 전체 +1
			pq.empl(x-bias);//2) x 이하 -1
			//3) 결과적으로 x이상만 +1됨
		}
	}
	void add_bias(int x){bias+=x;}//그래프 x축 평행이동
	PQMax<int> pq;
	int ans=0,bias=0;
};
