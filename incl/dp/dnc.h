#pragma once
#include "core/base.h"

//d[i][j]=min{k<j}(d[i−1][k]+c[k][j])
//opt[i][j]≤opt[i][j+1]을 만족할때 사용가능. opt[i][j]는 dp[i][j]점화식에서 최적인 k값
//충분조건: a<b, c<d -> f(a,c)+f(b,d)<=f(a,d)+f(b,c) (사각부등식보다 강력) (boj14636)
void dnc(Arr<int>& a, const Arr<int>& b, function<int(int,int)> c, int s, int e, int ks, int ke){
	if(e-s<=0)return;
	int m=(s+e)/2,km=ks;
	for(int k=km;k<ke;k++)
		if(a[m]>b[k-1]+c(k,m))
			a[m]=b[k-1]+c(k,m),km=k;
	dnc(a,b,c,s,m,ks,km+1),dnc(a,b,c,m+1,e,km,ke);
}