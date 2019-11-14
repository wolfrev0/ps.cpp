#pragma once
#include "Core.h"

template<typename T>
T fastpow(const T& a, int p) {
	if (p==0)
		return T(1);
	T tmp=fastpow(a, p/2);
	if (p%2)
		return tmp*tmp*a;
	return tmp*tmp;
}

/*
Adjust Formaula
xgcd(a,b) solves ax+by=gcd(a,b)=g
ax+by=c satisfied iff c=g*k
so, do x*=k and y*=k.

if (x,y) is one of root, (x+t*b/g, y-t*a/g) is also root.(t is arbitary integer)
if x and y have bounds, solve that inequalities.
For example, I have one lbx(lower bound x) and one lby(lower bound y).
I will find the root which is the closest to lbx.
solve x+t*b/g<lbx and x+t*b/g>=lbx consecutively.
then, all of big x go to small, and next all small thing go to big|equal to lbx
now, we got proper t for lbx, and check if y-t*a/g>=lby.(cuz (x,y)->(x+t*b/g, y-t*a/g))
if it is not satisfied, solve inequality for y similarly.
if adjusted x for satisfying y is not satisfied, this formula has no solution.

Maybe simpler solution exist. see	(jung2381187, koosaga)'s code at boj_11661
linearity?
*/
struct XGCD{i64 g; i64 x; i64 y;};
XGCD xgcd(i64 a, i64 b) {
		if (b==0)
				return {a,1,0};
		auto res = xgcd(b, a%b);
		return {res.g, res.y, res.x-(a/b)*res.y};
}
XGCD XGCDtolb(XGCD a, i64 lbx, i64 lby){
	if(0)
		throw "no root";
	return {};
	//return minimum a which satisfies lb<a
}
XGCD XGCDtoub(XGCD a, i64 ubx, i64 uby){
	if(0)
		throw "no root";
	return {};
	//return maximum a which satisfies a<ub
}

bool is_prime(i64 n){
	if(n<2)
		return false;
	for(i64 i=2;i*i<=n;i++){
		if(!(n%i))
			return false;
	}
	return true;
}

bool miller_rabin(i64 n){
	return true;
}

Arr<i64> factorization(i64 n){
	i64 cur=n;
	Arr<i64> ret;
	for(i64 i=2; i*i<=n; i++)
		while (!(cur%i)){
			cur/=i;
			ret.pushb(i);
		}
	if (cur>1)
		ret.pushb(cur);
	return ret;
}

Arr<i64> divisors(i64 n){
	Arr<i64> ret, tmp;
	for(i64 i=1; i*i<=n; i++){
		if (n%i==0){
			ret.pushb(i);
			if (i!=n/i)
				tmp.pushb(n/i);
		}
	}
	reverse(all(tmp));
	ret.insert(ret.end(), all(tmp));
	return ret;
}

//nloglog(n)
Arr<bool> sieve_prime(int ub){
	Arr<bool> ret(ub, true);
	ret[0]=ret[1]=false;
	for (i64 i=2; i*i<ub; i++) {
		if (!ret[i])
			continue;
		for (i64 j=i*i; j<ub; j+=i)
			ret[j]=false;
	}
	return ret;
}

//nlogn (harmony series)
//can apply to calculate (low constant factor)sieve_numdiv, sieve_sumdiv, etc.
Arr<Arr<int>> sieve_divs(int ub){
	Arr<Arr<int>> ret(ub);
	for (i64 i=1; i<ub; i++) {
		for (i64 j=i; j<ub; j+=i)
			ret[j].pushb(i);
	}
	return ret;
}

int eulerphi(int n){return 0;}

//floor(log(n))
int lgf(i64 n, int base=2){
	int ret=0;
	while (n)
		n/=base, ret++;
	return ret-1;
}

//ceil(log(n))
int lgc(i64 n, int base=2) {
	int ret=0;
	int rem=0;
	while (n)
		rem+=n%base, n/=base, ret++;
	return ret-(rem<=1);
}

int sqrt_f(i64 n){
	i64 i=1;
	while(i*i<=n)
		i++;
	return i-1;
}

int sqrt_c(i64 n){
	i64 i=1;
	while(i*i<n)
		i++;
	return i;
}

template<typename T>
Arr<T> factorials(T n){
	Arr<T> ret(int(n)+1);
	ret[0]=1;
	cfor(i, 1, n)
		ret[i]=ret[i-1]*i;
	return ret;
}

//recommanded T=ModNum. i64 can easily overflow.
template<typename T>
T binom(T n, T k){
	if(k>n/2)
		return binom(n, n-k);
	if(k==0)
		return 1;
	auto f=factorials(n);
	return f[int(n)]/(f[int(k)]*f[int(n-k)]);
}

template<typename T>
Arr<Arr<T>> binom_dp(T n, T k){
	Arr<Arr<T>> ret(n, Arr<T>(k));

	return ret;
}

Arr<int> to_digits(i64 n){
	Arr<int> ret;
	while(n)
		ret.pushb(n%10), n/=10;
	return ret;
}

//chinese remainder theorem
void crt(){
}