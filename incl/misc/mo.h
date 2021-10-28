#pragma once
#include "core/base.h"

//NOTE: 캐싱안하면 정렬이 log^2되서 느림
template<int n>int hilbert_ord(int x,int y){//n-bit order
	int d=0;
	for(int i=n-1;~i;i--){
		bool rx=x>>i&1,ry=y>>i&1;
		d=d<<2|(rx*3^ry);
		if(!ry){
			if(rx) x=(1<<n)-x,y=(1<<n)-y;
			swap(x,y);
		}
	}
	return d;
}
// template<int B>
struct MOQ{
	int s,e,i,o;
	MOQ(int s,int e,int i):s(s),e(e),i(i),o(hilbert_ord<30>(s,e)){}
	bool operator<(const MOQ& r)const{return o<r.o;}
	// bool operator<(const MOQ& r)const{return pint{s/B,e/B}<pint{r.s/B,r.e/B};}
};