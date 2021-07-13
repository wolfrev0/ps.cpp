#pragma once
#include "core/base.h"

//아래 링크자료 정독하자
//https://rkm0959.tistory.com/category/PS/PS%20%EC%A0%95%EC%88%98%EB%A1%A0%20%EA%B0%80%EC%9D%B4%EB%93%9C

//<Adjust Formaula>
// xgcd(a,b) solves ax+by=gcd(a,b)=g
// ax+by=c satisfied iff c=g*k     so, do x*=k and y*=k.
// if (x,y) is one of root, (x+t*b/g, y-t*a/g) is also root.
tint xgcd(i64 a, i64 b) {
	if(!b) return {a, 1, 0};
	auto [g, x, y] = xgcd(b, a % b);
	return {g, y, x - (a / b) * y};
}
int eutot(int n) {
	int r = 1, x = n;
	for(int i = 2; i * i <= n; i++) {
		if(x % i) continue;
		while(x % i == 0) x /= i, r *= i;
		r = r / i * (i - 1);
	}
	if(x > 1) r *= x - 1;
	return r;
}

#include "misc/i128.h"
bool miller_rabin(u64 n){
	func(u64,fp,u64 x,u64 p){
		if(!p) return 1;
		i128 z=fp(x,p/2);
		return z*z%n*(p&1?x:1)%n;
	};
	func(bool,test,u64 n,u64 a){
		u64 d=n-1;
		while(d%2==0){
			if(fp(a,d)==n-1)return true;
			d>>=1;
		}
		u64 tmp=fp(a,d);
		return tmp==n-1||tmp==1;
	};
	if(n<=1)return false;
	if(n<=10000){
		for(u64 i=2;i*i<=n;i++)
			if(n%i==0)
				return false;
		return true;
	}
	bool ret=true;
	for(auto i:{2,325,9375,28178,450775,9780504,1795265022})//{2,7,61}<=2^32
		ret&=test(n,i);
	return ret;
}

// chinese remainder theorem
// https://en.wikipedia.org/wiki/Chinese_remainder_theorem#Generalization_to_non-coprime_moduli
// x = r (mod m), pair<r,m>
pair<i64, i64> crt(Arr<pair<i64, i64>> a) {
	i64 r1 = 0, m1 = 1;
	for(auto [r2, m2] : a) {
		i64 g = gcd(m1, m2);
		if(r1 % g != r2 % g) return {-1, -1};
		auto [_1, x, y] = xgcd(m1 / g, m2 / g);
		i64 m3 = lcm(m1, m2);
		i64 r3 = m2 / g * r1 % m3 * y % m3 + m1 / g * r2 % m3 * x % m3;
		r1 = r3 < 0 ? r3 + m3 : r3;
		m1 = m3;
	}
	return {r1, m1};
}
void discrete_log() {}  // baby step giant step
void discrete_sqrt() {}  // tonelli-shanks