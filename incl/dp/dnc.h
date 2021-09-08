#pragma once
#include "core/base.h"

//d[i][j]=min{k<j}(d[i−1][k]+c[k][j])
//a[t][i]는 d[t][i] Formula가 minimum이 되는 k들중 최소값이라 할때 a[t][i]≤a[t][i+1]
//Note: c가 사각부등식을 만족하면 위 제약조건이 성립됨. 사용법 BOJ 11001 참고
void dnc(Arr<int>& a, const Arr<int>& b, function<int(int,int)> c, int s, int e, int ks, int ke){
	int m=(s+e)/2,km=ks;
	for(int k=km;k<ke;k++)
		if(a[m]>b[k-1]+c(k,m))
			a[m]=b[k-1]+c(k,m),km=k;
	if(e-s>1)
		dnc(a,b,c,s,m,ks,km+1),dnc(a,b,c,m,e,km,ke);
}