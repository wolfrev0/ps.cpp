#pragma once
#include "Core.h"

int log_f(i64 n, int base=2){int ret=0; while(n)n/=base,ret++; return ret-1;}
int log_c(i64 n, int base=2) {int ret=0,rem=0; while(n)rem+=n%base,n/=base,ret++; return ret-(rem<=1);}
int sqrt_f(i64 n){i64 i=1; while(i*i<=n)i++; return i-1;}
int sqrt_c(i64 n){i64 i=1; while(i*i<n)i++; return i;}

template<class T>
Arr<T> factorials(T n){
	Arr<T> ret(int(n)+1);
	ret[0]=1;
	forc(i, 1, n)
		ret[i]=ret[i-1]*i;
	return ret;
}
template<class T>
T binom(T n, T k){
	if(k>n/2)
		return binom(n, n-k);
	if(k==0)
		return 1;
	auto f=factorials(n);
	return f[int(n)]/(f[int(k)]*f[int(n-k)]);
}
template<class T>
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

//<Adjust Formaula>
//xgcd(a,b) solves ax+by=gcd(a,b)=g
//ax+by=c satisfied iff c=g*k     so, do x*=k and y*=k.
//if (x,y) is one of root, (x+t*b/g, y-t*a/g) is also root.(t is arbitary integer)
//when x,y have boundary, see (jung2381187, koosaga)'s code at boj_11661, linearity?
//<Multivariable Linear Deophantine>
//ax+by+cz=k => gcd(a,b)w+cz=k && ax+by=gcd(a,b)w (extend it recursively)

//recommand to use python
tuple<int,int,int> xgcd(i64 a, i64 b) {
	if (b==0) return {a,1,0};
	auto [g,x,y]=xgcd(b, a%b);
	return {g,y,x-(a/b)*y};
}
tuple<int,int,int> XGCDtolb(tuple<int,int,int> a, i64 lbx, i64 lby){
	if(0) throw "no root";
	return {};
	//return minimum a which satisfies lb<a
}
tuple<int,int,int> XGCDtoub(tuple<int,int,int> a, i64 ubx, i64 uby){
	if(0) throw "no root";
	return {};
	//return maximum a which satisfies a<ub
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
int eutot(int n){
	int r=1, x=n;
	for(int i=2;i*i<=n;i++){
		if(x%i) continue;
		while(x%i==0)
			x/=i,r*=i;
		r=r/i*(i-1);
	}
	if(x>1)
		r*=x-1;
	return r;
}

template<class T>
T fp(const T& a, int p) {
	if(!p)return T(1);
	T tmp=fp(a, p/2);
	if (p%2)
		return tmp*tmp*a;
	return tmp*tmp;
}
i64 fpm(i64 x, i64 p, i64 m){
	if(!p)return 1;
	i64 z=fpm(x,p/2,m);
	return z*z%m*(p%2?x:1)%m;
}
i64 modinv(i64 a, i64 m){return fpm(a,m-2,m);}

//chinese remainder theorem
//https://en.wikipedia.org/wiki/Chinese_remainder_theorem#Generalization_to_non-coprime_moduli
//x = r (mod m), pair<r,m>
pair<i64,i64> crt(Arr<pair<i64,i64>> a){
	i64 r1=0, m1=1;
	for(auto [r2,m2]:a){
		i64 g=gcd(m1,m2);
		if(r1%g != r2%g) return {-1,-1};
		auto [_1,x,y] = xgcd(m1/g,m2/g);
		i64 m3=lcm(m1,m2);
		i64 r3=m2/g*r1%m3*y%m3+m1/g*r2%m3*x%m3;
		r1=r3<0?r3+m3:r3;
		m1=m3;
	}
	return {r1,m1};
}

//baby step giant step
void discrete_log(){
}