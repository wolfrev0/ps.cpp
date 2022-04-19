#pragma once
#include "core/base.h"

//TODO: 홀짝 나눠서 올라갔다가 내려갔다가 하도록 하면 더 빨라진다고 함
//이게 힐베르트에서 하라는건지 그냥 생mo에서 하라는건지는 잘 몰루
//힐베르트가 대충 tsp근사하는건데, 그냥 모에서 ↑↑↑↑만 하는것보단 ↑↓↑↓하는게 더 짧기때문?
//홀수는 오름차순 짝수는 내림차순 하면 되나? 아무튼 관련정보 찾아보거나 그냥 짜보자.
//NOTE: 캐싱안하면 정렬이 log^2되서 느림
template<int n>int hilbert_ord(int x,int y){//n-bit order
	int d=0;
	for(int i=n-1;~i;i--){
		bool rx=x>>i&1,ry=y>>i&1;
		d=d<<2|(rx*3^ry);
		if(!ry){
			if(rx)x=(1<<n)-x,y=(1<<n)-y;
			swap(x,y);}}
	return d;}
// template<int B>
struct MOQ{
	int s,e,i,o;
	MOQ(int s,int e,int i):s(s),e(e),i(i),o(hilbert_ord<30>(s,e)){}
	bool operator<(const MOQ& r)const{return o<r.o;}
	// bool operator<(const MOQ& r)const{return pint{s/B,e/B}<pint{r.s/B,r.e/B};}
};