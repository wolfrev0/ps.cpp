#pragma once
#include "core/base.h"

#pragma GCC optimize ("Ofast")
template<class T> struct Mat{
	int n, m;
	Arr<Arr<T>> a;
	Mat(int n,int m,bool one=false):n(n),m(m),a(n,Arr<T>(m)){
		if(!one)return;
		for(int i=0;i<min(n,m);i++)a[i][i]=1;
	}
	Mat(int n,int m,initializer_list<int> li):Mat(n,m){
		auto it=li.begin();
		for(int i=0;i<n;i++)for(int j=0;j<m;j++)a[i][j]=*it++;
	}
	Mat<T> operator*(const Mat<T>& r)const{
		assert(m==r.n);
		Mat<T> ret(n,r.m);
		for(int i=0;i<n;i++)
			for(int j=0;j<r.m;j++)
				for(int k=0;k<m;k++)
					ret.a[i][j]+=a[i][k]*r.a[k][j];
		return ret;
	}
	Mat<T> transpose(){
		Mat<T> ret(m,n);
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				ret.a[j][i]=a[i][j];
		return ret;
	}
	Mat<T> sub(int r,int c,int rn,int rm)const{
		Mat<T> ret(rn,rm);
		for(int i=0;i<rn;i++)
			for(int j=0;j<rm;j++)
				ret.a[i][j]=a[r+i][c+j];
		return ret;
	}
	Mat<T> inv(){
		if(n!=m)throw "No MatInv";
		assert(n==m);
		Mat<T> tmp(n,n*2);
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				tmp.a[i][j]=a[i][j];
		for(int i=0;i<n;i++)
			tmp.a[i][n+i]=1;
		if(tmp.RREF(n)!=n)throw "No MatInv";
		return tmp.sub(0,n,n,n);
	}
	int REF(bool pv_fix) {
		int pi=0;
		int i=0;
		for(;i<n;i++){
			while(pi<m&&!a[i][pi]){
				if(!pv_fix){
					int j=i+1;
					for(;j<n;j++)
						if(a[j][pi])break;
					if(j<n){swap(a[i],a[j]);break;}
				}
				pi++;
			}
			if(pi==m)break;
			if(a[i][pi]){
				for(int j=m-1;j>=pi;j--)a[i][j]/=a[i][pi];
				for(int j=i+1;j<n;j++){
					auto z=a[j][pi];
					if(!z)continue;
					for(int k=pi;k<m;k++)a[i][k]*=z;
					for(int k=pi;k<m;k++)a[j][k]-=a[i][k];
					for(int k=pi;k<m;k++)a[i][k]/=z;
				}
			}
			pi++;
		}
		return rank=i;
	}
	int RREF(int rm){REF(false);flipX(rank),flipY(rm),REF(true),flipY(rm),flipX(rank);return rank;}
	void flipX(int rn){for(int i=0;i<rn/2;i++)for(int j=0;j<m;j++)swap(a[i][j],a[rn-1-i][j]);}
	void flipY(int rm){for(int i=0;i<n;i++)for(int j=0;j<rm/2;j++)swap(a[i][j],a[i][rm-1-j]);}
private:
	int rank=-1;
};

template<typename T> ostream& operator<<(ostream& s, const Mat<T>& mat) {
	for(int i=0;i<mat.n;i++,s<<'\n')
		for(int j=0;j<mat.m;j++)
			s<<mat.a[i][j]<<' ';
	return s;
}