#pragma once
#include "core.h"

//DEFINITIONS
//d[i][j] = min{-1<=k<=j}(d[i-1][k]+c[k+1][j+1]
//i: 전체 dp단계
//j: 현재 dp단계의 계산할 index
//k: 현재 d[i][j]를 계산하는데 사용하는 iter변수.
//	k in [-1,j]이므로 dp와 cost가 둘다 길이0인 구간을 지원해야 함.
//d: dp배열. -1인 인덱스를 지원해야함.
//c: cost함수. c(s,e)로 반열린구간[s,e)의 코스트를 의미. 길이0인 구간을 지원해야함
//코드에서 dp1=dp[i], dp0=dp[i-1]이다.

//NOTES
//opt[i][j]≤opt[i][j+1]을 만족할때 사용가능. opt[i][j]는 dp[i][j]점화식에서 최적인 k값
//충분조건: a<b,c<d -> c(a,c)+c(b,d)<=c(a,d)+c(b,c) (사각부등식보다 강력) (boj14636)
//pbs처럼 라운드별 자료구조 스위핑처리를 할 수 있다. cost를 전처리나 온라인으로 계산하기는 어려운데 스위핑하면 계산할 수 있을때 유용함. boj10076
void dnc(Arr<int>& dp1,const Arr<int>& dp0,function<int(int,int)> c,int s,int e,int ks,int ke){
	if(e-s<=0)return;
	int m=(s+e)/2,km=ks;
	for(int k=ks;k<ke;k++)
		if(dp1[m]>dp0[k]+c(k+1,m+1))
			dp1[m]=dp0[k]+c(k+1,m+1),km=k;
	dnc(dp1,dp0,c,s,m,ks,km+1),dnc(dp1,dp0,c,m+1,e,km,ke);
}
void dnc(Arr<int>& dp1,const Arr<int>& dp0,function<int(int,int)> c,int s,int e){dnc(dp1,dp0,c,s,e,s-1,e);}
