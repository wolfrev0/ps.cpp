#pragma once
#include "Core.h"

template<typename T>
T fastpow(const T& a, int p) {
	if (p==0)
		return a.one();
	T tmp=fastpow(a, p/2);
	if (p%2)
		return tmp*tmp*a;
	return tmp*tmp;
}

struct XGCD{i64 g; i64 x; i64 y;};
XGCD xgcd(i64 a, i64 b) {
    if (b==0)
        return {a,1,0};
    auto res = xgcd(b, a%b);
    return {res.g, res.y, res.x-(a/b)*res.y};
}

vector<i64> factorization(i64 n){
	i64 cur=n;
	vector<i64> ret;
	for(i64 i=2; i*i<=n; i++)
		while (!(cur%i)){
			cur/=i;
			ret.push_back(i);
		}
	if (cur>1)
		ret.push_back(cur);
	return ret;
}

vector<i64> divisors(i64 n){
	vector<i64> ret, tmp;
	for(i64 i=1; i*i<=n; i++){
		if (n%i==0){
			ret.push_back(i);
			if (i!=n/i)
				tmp.push_back(n/i);
		}
	}
	reverse(tmp.begin(), tmp.end());
	ret.insert(ret.end(), tmp.begin(), tmp.end());
	return ret;
}

//nloglog(n)
vector<bool> sieve_prime(int ub){
	vector<bool> ret(ub, true);
  ret[0]=ret[1]=false;
	for (i64 i=2; i*i<=ub; i++) {
		if (!ret[i])
			continue;
		for (i64 j=i*i; j<ub; j+=i)
			ret[j]=false;
	}
	return ret;
}

//nlogn (harmony series)
vector<vector<int>> sieve_divs(int n){
	vector<vector<int>> ret(n);
	for (i64 i=2; i*i<=n; i++) {
		for (i64 j=i+i; j<n; j+=i)
			ret[j].push_back(i);
	}
	return ret;
}

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
vector<T> factorials(T n){
  vector<T> ret(int(n)+1);
  ret[0]=1;
  forc(i, 1, n)
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
vector<vector<T>> binom_dp(T n, T k){
  vector<vector<T>> ret(n, vector<T>(k));

  return ret;
}

vector<int> to_digits(i64 n){
  vector<int> ret;
  while(n){
    ret.push_back(n%10);
    n/=10;
  }
  return ret;
}