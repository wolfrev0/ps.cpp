#pragma once
#include "core/base.h"

//회전변환시 계수 1/sqrt(2)를 제거하고 사용.
//fi: -n~n, se: 0~2n
//boj2570 참고
pint rot45(pint a){return {a.fi-a.se,a.fi+a.se};}
pint rot45i(pint a){MUST((a.fi+a.se)&1^1); return {(a.fi+a.se)>>1,(-a.fi+a.se)>>1};}

//fi+n/2*2, se로 사용하면 양수 0~2n만 사용하고, 합이 짝수인것만 유효한것도 동일하다
pint rot45p(pint a,int n){return {a.fi-a.se+n/2*2,a.fi+a.se};}
pint rot45pi(pint a,int n){MUST((a.fi+a.se)&1^1); return {(a.fi-n/2*2+a.se)>>1,(-a.fi+n/2*2+a.se)>>1};}
