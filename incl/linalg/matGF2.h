#pragma once
#include "core/base.h"

#if !(DEBUG)
	#pragma GCC optimize ("Ofast")
#endif
//NOTE: Mat<m>(n)은 n*m행렬이다.
template<int m> struct MatGF2{
	const int n;
	Arr<bitset<m>> a;
	MatGF2(int n):n(n),a(n){}
	Arr<int> operator*(const bitset<m>& v)const{
		//NOTE: m*v 말고 v*m이 필요한 경우 전치시키면 됨
		Arr<int> ret(n);
		for(int i=0;i<n;i++)
			ret[i]=(a[i]&v).count()%2;
		return ret;
	}

	int REF(bool pv_fix){
		int pi=0,i=0;
		for(;i<n;i++){
			while(pi<m&&a[i][pi]==0){
				if(!pv_fix){
					int j=i+1;
					for(;j<n;j++)
						if(a[j][pi])break;
					if(j<n){swap(a[i],a[j]);break;}
				}
				pi++;
			}
			if(pi==m)break;
			if(a[i][pi])for(int j=i+1;j<n;j++)if(a[j][pi])a[j]^=a[i];
			pi++;
		}
		return rank=i;
	}
	int RREF(int rm){REF(false),flipX(rank),flipY(rm),REF(true),flipY(rm),flipX(rank);return rank;}
	void flipX(int rn){for(int i=0;i<rn/2;i++)swap(a[i],a[rn-1-i]);}
	void flipY(int rm){
		for(int i=0;i<n;i++){
			for(int j=0;j<rm/2;j++){
				bool z=a[i][j];
				a[i][j]=a[i][rm-1-j],a[i][rm-1-j]=z;
			}
		}
	}
private:
	int rank=-1;
};
template<int m> ostream& operator<<(ostream& os, const MatGF2<m>& mat){
	for(int i=0;i<mat.n;i++){
		for(int j=0;j<m;j++)
			osprint(os,mat.a[i][j],' ');
		osprint(os,'\n');
	}
	return os;
}

//https://www.acmicpc.net/source/64632629
//https://atcoder.jp/contests/abc313/submissions/44317320 이건 테케 하나 틀리는데 이유를 모르겠다.
template<int N>
struct MatGF2Sq: public MatGF2<N>{
	const int n;
	MatGF2Sq(int n=N):MatGF2<N>(N),n(n){
		//[n,N)은 미사용이므로 I로 채움
		for(int i=n;i<N;i++)
			this->a[i][i]=1;
	}
	MatGF2Sq inv(){
		MatGF2<N*2> tmp(n);
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				tmp.a[i][j]=this->a[i][j];
		for(int i=0;i<n;i++)
			tmp.a[i][n+i]=1;
		if(tmp.RREF(n)!=n)
			throw "No MatInv";
		MatGF2Sq<N> ret;
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				ret.a[i][j]=tmp.a[i][n+j];
		return ret;
	}
};
template<int N> ostream& operator<<(ostream& os, const MatGF2Sq<N>& mat){
	for(int i=0;i<mat.n;i++){
		for(int j=0;j<mat.n;j++)
			osprint(os,mat.a[i][j],' ');
		osprint(os,'\n');
	}
	return os;
}