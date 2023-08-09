#pragma once
#include "core/base.h"

// NOTE: bitmask>>64 cause UB, expected 0, cause f(x)=x, See #1, https://stackoverflow.com/questions/18918256/is-right-shift-undefined-behavior-if-the-count-is-larger-than-the-width-of-the-t
bool ispow2(int n){return (n&-n)==n and n;}
u64 to_mask(int i){return 1ULL<<i;}
int to_num(u64 mask){assert(ispow2(mask));return flg2(mask);}
void subsetk(int n,int k,const function<void(int)>&f){
	for(int i=(1<<k)-1;i and i<(1<<n);){
		int a=i&-i,b=i+a;
		f(i);
		i=((i^b)>>2)/a|b;
	}
}
u64 bitreverse(u64 n) {
    n = (n >> 32) | (n << 32);
    n = ((n & 0xFFFF0000FFFF0000ULL) >> 16) | ((n & 0x0000FFFF0000FFFFULL) << 16);
    n = ((n & 0xFF00FF00FF00FF00ULL) >> 8) | ((n & 0x00FF00FF00FF00FFULL) << 8);
    n = ((n & 0xF0F0F0F0F0F0F0F0ULL) >> 4) | ((n & 0x0F0F0F0F0F0F0F0FULL) << 4);
    n = ((n & 0xCCCCCCCCCCCCCCCCULL) >> 2) | ((n & 0x3333333333333333ULL) << 2);
    n = ((n & 0xAAAAAAAAAAAAAAAAULL) >> 1) | ((n & 0x5555555555555555ULL) << 1);
    return n;
}

//Dynamic size bitset
//Not tested
//NOTE: array는 lr증가인데 bit는 rl증가임
//shift interface는 lr증가(array방식)를 사용함
// Bitset().on(0)>>0=8000000000000000
// Bitset().on(0)>>1=4000000000000000
// Bitset().on(0)>>2=2000000000000000
// Bitset().on(0)>>3=1000000000000000
// Bitset().on(0)>>4=0800000000000000
// Bitset().on(0)>>5=0400000000000000
// NOTE: 일반 숫자 bit연산에선 rl방식이므로, 여기서 bit연산은 shift좌우반전해야됨. 아래 제출 참고
// https://codeforces.com/contest/1856/problem/E2
struct Bitset{
	vector<u64> a;
	Bitset(int n=64):a((n+63)/64){}
	bool get(int idx){
		while(sz(a)*64<=idx)
			a.emplace_back();
		return a[idx/64]&1ull<<idx%64;
	}
	Bitset& on(int idx){
		while(sz(a)*64<=idx)
			a.emplace_back();
		a[idx/64]|=1ull<<idx%64;
		return *this;
	}
	Bitset& off(int idx){
		while(sz(a)*64<=idx)
			a.emplace_back();
		a[idx/64]&=~(1ull<<idx%64);
		return *this;
	}
	Bitset& toggle(int idx){
		while(sz(a)*64<=idx)
			a.emplace_back();
		a[idx/64]^=1ull<<idx%64;
		return *this;
	}
	Bitset& shiftL(int k){
		throw "TBD";
		return *this;
	}
	Bitset& shiftR(int k){
		for(int i=0;i<(k+63)/64;i++)
			a.emplace_back();
		int i=sz(a)-1;
		int q=k/64, r=k%64;
		if(r==0){
			for(;i-q>=0;i--)
				a[i] = a[i-q];
		}else{
			for(;i-q-1>=0;i--)
				a[i] = a[i-q]<<r | a[i-q-1]>>(64-r);
			if(i-q>=0)
				a[i] = a[i-q]<<r, i--;
		}
		for(;i>=0;i--)
			a[i] = 0;
		return *this;
	}
	Bitset& or_bitwise(const Bitset& r){
		a.resize(max(sz(a),sz(r.a)));
		for(int i=0;i<sz(r.a);i++)
			a[i]|=r.a[i];
		return *this;
	}
	Bitset& and_bitwise(const Bitset& r){
		a.resize(max(sz(a),sz(r.a)));
		for(int i=0;i<sz(a);i++)
			a[i]&=r.a[i];
		return *this;
	}
	Bitset& xor_bitwise(const Bitset& r){
		a.resize(max(sz(a),sz(r.a)));
		for(int i=0;i<sz(a);i++)
			a[i]^=r.a[i];
		return *this;
	}
	bool operator[](int i){return get(i);}
	Bitset operator<<(int k){return Bitset(*this).shiftL(k);}
	Bitset operator>>(int k){return Bitset(*this).shiftR(k);}
	Bitset& operator<<=(int k){return shiftL(k);}
	Bitset& operator>>=(int k){return shiftR(k);}
	Bitset operator|(const Bitset& r){return Bitset(*this).or_bitwise(r);}
	Bitset& operator|=(const Bitset& r){return or_bitwise(r);}
	
	Bitset& or_shiftR(int k){// b|=b<<k
		int i=sz(a)-1;
		int q=k/64, r=k%64;
		if(r==0){
			for(;i-q>=0;i--)
				a[i] = a[i-q];
		}else{
			for(;i-q-1>=0;i--)
				a[i] |= a[i-q]<<r | a[i-q-1]>>(64-r);
			if(i-q>=0)
				a[i] |= a[i-q]<<r;
		}
		return *this;
	}
};

ostream& operator<<(ostream&os, const Bitset& b){
	// //number style print
	// for(auto i=b.a.rbegin();i!=b.a.rend();i++)
	// 	cout<<bitset<64>(*i);

	//array style print
	for(auto i:b.a)
		cout<<hex<<setw(16)<<setfill('0')<<bitreverse(i);
	cout<<dec;

	return os;
}