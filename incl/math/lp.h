#pragma once
#include "core/base.h"
#include "misc/util.h"

//입력: Ax(<=,>=)b, obj (b>=0)
//출력: maximize obj*x
//numeric stability is sensitive by M
template<class T=f64,int M>
void dualize(Arr<Arr<T>> &a,Arr<T> &b,Arr<char>& leq,Arr<T>& obj){
	int m=sz(a), n=sz(a[0]);
	for(int i=0;i<m;i++){
		if(!leq[i]){
			for(auto& i:a[i])i=-i;
			b[i]=-b[i];
			leq[i]=!leq[i];
		}
	}
	transpose(a);
	swap(b,obj);
	leq=Arr<char>(n,false);
	for(int i=0;i<n;i++)
		if(b[i]<0){
			for(auto& i:a[i])i=-i;
			b[i]=-b[i];
			leq[i]=!leq[i];
		}
	for(auto& i:obj)i=-i;
}
template<class T=f64,int M>
T simplex(Arr<Arr<T>>& a,Arr<T>& b,Arr<char>&leq, Arr<T>& obj){
	for(auto i:b)assert(i>=0);
	int m=sz(a), n=sz(a[0]);
	if(m>n){
		dualize<T,M>(a,b,leq,obj);
		return -simplex<T,M>(a,b,leq,obj);
	}
	
	int s=0;
	for(int i=0;i<m;i++){
		if(!leq[i]){
			for(auto&row:a)row.pushb(0);
			a[i][-1]=-1,s++;
		}
	}

	func(void,elim,int r1,int r2,int c){//elim r2
		if(r1==r2){T x=a[r1][c]; for(auto& i:a[r1])i/=x;}
		else{
			T x=a[r2][c]/a[r1][c]; if(!x)return;
			for(int i=0;i<n+s+m+2;i++)
				a[r2][i]-=x*a[r1][i];
		}
	};

	//n vars, s slacks(-1), m slacks(1), 1 z, 1 b_value
	Arr<int> p(m);//행의 기본변수
	obj.resize(n+s+m+2);
	for(int i=0;i<m;i++)
		a[i].resize(n+s+m+2),a[i][p[i]=n+s+i]=1,a[i][-1]=b[i],obj[p[i]]=leq[i]?0:-M;
	
	//z=f(x) == z-f(x)=0
	for(auto &i:obj)i=-i;
	obj[-2]=1;
	a.emplb(obj);
	//shape(a): (m+1)*(n+s+m+2)

	for(int i=0;i<m;i++)
		elim(i,m,p[i]);

	while(true){
		int ev=0,lvi=0;
		for(int i=0;i<n+s+m;i++)
			ev=a[-1][ev]>a[-1][i]?i:ev;
		if(a[-1][ev]>=0)break;
		for(int i=0;i<m;i++)
			lvi=a[i][ev]>0&&(a[lvi][ev]<=0||a[lvi][-1]/a[lvi][ev]>a[i][-1]/a[i][ev])?i:lvi;
		if(a[lvi][ev]&&a[lvi][-1]/a[lvi][ev]<0) throw "unbounded";
		for(int i=0;i<m+1;i++)elim(lvi,i,ev);
		p[lvi]=ev;
	}
	//역추적 잘 모르겠다. 가우스소거 필요한듯?
	//if(?) throw "infeasible"
	return a[-1][-1];
}