#pragma once
#include "core/base.h"

// #pragma GCC optimize ("Ofast")
//입력: Ax(<=,>=)b, obj
//출력: val, argmax (maximize obj*x)
//numeric stability is sensitive by M
template<class T=f64,int M>
pair<T,Arr<T>> simplex(Arr<Arr<T>> a,Arr<T> b,Arr<bool>leq,Arr<T> obj){
	int m=sz(a), n=sz(a[0]);

	if(m>n*1.2){
		//TODO: dualize
	}

	//if b<0, use bigM
	// int s=0;
	// for(int i=0;i<m;i++)
	// 	if(b[i]<0){
	// 		s++;
	// 		for(int j=0;j<m;j++)
	// 			a[j].emplb(0);
	// 		for(int j=0;j<n+s;j++)
	// 			a[i][j]=-a[i][j],b[i]=-b[i];
	// 		a[i][-1]=-1;
	// 	}
	//now, b>=0

	//이렇게 미리 할수가 없는듯? (슬랙변수들) -x추가하고나서 +y추가할때 y의 obj를 M으로 설정해야함

	Arr<int> p(m+1);//행의 기본변수
	Arr<T>v(n+m+2);//변수값
	//n vars, s slacks, m slacks, 1 z, 1 b_value
	for(int i=0;i<m;i++)
		a[i].resize(n+m+2),a[i][p[i]=n+i]=1,v[p[i]]=a[i][-1]=b[i];
	p[-1]=n+m;
	a.emplb(Arr<T>(n+m+2));
	for(int i=0;i<n;i++)
		a[-1][i]=-obj[i];
	a[-1][n+m]=1;
	//a: (m+1)*(n+m+2) matrix
	
	while(true){
		int ev=0,lvi=0;
		for(int i=0;i<n+m;i++)
			ev=a[-1][ev]>a[-1][i]?i:ev;
		if(a[-1][ev]>=0)break;
		for(int i=0;i<m;i++)
			lvi=a[i][ev]>0&&(a[lvi][ev]<0||a[lvi][-1]/a[lvi][ev]>a[i][-1]/a[i][ev])?i:lvi;
		if(a[lvi][-1]/a[lvi][ev]<0) throw "unbounded";
		T t=a[lvi][ev];
		for(auto&i:a[lvi])i/=t;
		for(int i=0;i<m+1;i++){
			if(i==lvi)continue;
			t=a[i][ev];
			for(int j=0;j<n+m+2;j++)
				a[i][j]-=t*a[lvi][j];
		}
		p[lvi]=ev;
	}
	return {a[-1][-1],v};
}