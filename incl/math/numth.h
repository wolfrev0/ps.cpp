#pragma once
#include "core/base.h"
#include "misc/i128.h"
#include "misc/random.h"

int flg(i64 n,int base=2) {
	int ret=0;
	while(n) n/=base,ret++;
	return ret-1;
}
int clg(i64 n,int base=2) {
	int ret=0,rem=0;
	while(n) rem+=n%base,n/=base,ret++;
	return ret-(rem<=1);
}

template<class T> T pow_dnc(T n,int m){
	if(m==0)return T(1);
	T z=pow_dnc(n,m/2);
	return z*z*(m%2?n:T(1));
}
template<class T> T pow_dp(T n,int m){
	if(m==0)return T(1);
	static Arr<optional<T>> dp;
	dp.resize(max<int>(sz(dp),m+1));
	auto& r=dp[m];
	if(r)return r.value();
	return (r=pow_dp(n,m-1)*n).value();
}

template<class T> T factorial(int x){
	if(x<=1)return 1;
	static Arr<optional<T>> dp;
	dp.resize(max<int>(sz(dp),x+1));
	auto& r=dp[x];
	if(r)return r.value();
	return (r=factorial<T>(x-1)*x).value();
}

template<class T> T binomial(int x,int y){
	if(y<-1 or y>x) return 0;
	if(y==0 or y==x) return 1;
	if(x-y<y)
		y=x-y;
	return factorial<T>(x)/(factorial<T>(y)*factorial<T>(x-y));
}

Arr<i64> divisor(i64 n) {
	Arr<i64> r,s;
	for(i64 i=1;i*i<=n;i++)
		if(n%i==0){
			r.emplace_back(i);
			if(i!=n/i)
				s.emplace_back(n/i);
		}
	reverse(s.begin(),s.end());
	r.insert(r.end(),s.begin(),s.end());
	return r;
}
Arr<i64> factorize(i64 n) {
	i64 c=n;
	Arr<i64> r;
	for(i64 i=2;i*i<=n;i++)
		while(!(c%i)){
			c/=i;
			r.emplace_back(i);
		}
	if(c>1)r.emplace_back(c);
	return r;
}

#include "math/struct/mod.h"
//not tested
//a(r^0)+a/(r^1)+a/(r^2)+...+a/(r^n)
template<class T> T geom_sum(T a,T r,int n){
	assert(r!=1);
	if(n==inf<int>())return a/(1-r);
	return a*(1-r.pow(n+1))/(1-r);
}

//<Adjust Formaula>
// xgcd(a,b)solves ax+by=gcd(a,b)=g
// ax+by=c satisfied iff c=g*k     so,do x*=k and y*=k.
// if(x,y)is one of root,(x+t*b/g,y-t*a/g)is also root.
tint xgcd(i64 a,i64 b){
	if(!b)return{a,1,0};
	auto [g,x,y]=xgcd(b,a%b);
	return{g,y,x-(a/b)*y};
}
int modinv(int n,int m){auto [g,x,y]=xgcd(n,m);assert(g==1);while(x<0)x+=m;return x;}

int eutot(int n){
	int r=1,x=n;
	for(int i=2;i*i<=n;i++){
		if(x%i)continue;
		while(x%i==0)x/=i,r*=i;
		r=r/i*(i-1);
	}
	if(x>1)r*=x-1;
	return r;
}

bool miller_rabin(u64 n){
	dbg1("[deprecated] use faster version Rho::isprime");
	func(u64,fp,u64 x,u64 p){
		if(!p)return 1;
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

int lucas(int n,int m,int p){
	Arr<int> fac(p),inv(p*2);
	fac[0]=1;
	for(int i=1;i<p;i++)
		fac[i]=fac[i-1]*i%p;
	inv[p-1]=p-1;//willson
	for(int i=p-2;~i;i--)
		inv[i]=inv[i+1]*(i+1)%p;
	int ret=1;
	while(n||m){
		ret=ret*fac[n%p]%p*inv[m%p]%p*inv[n%p-m%p]%p;
		n/=p,m/=p;
	}
	return ret;
}

//chinese remainder theorem
//https://rkm0959.tistory.com/180?category=828364
//merge two equation [ x=a.fi(mod a.se),x=b.fi(mod b.se)]
//these are equivalent with
//x=a.se*y+a.fi=b.fi(mod b.se)
//=> a.se*y1+b.se*y2=b.fi-a.fi
//=> 이제 xgcd로 y1,y2 구할 수 있다. 정확히는 y1=t(mod b.se/g)를 알수있다.
//=> 위와 동치인 y1=t+b.se/g*m을 x=a.se*y1+a.fi에 대입하면
//=> x=a.se*b.se/g*m+a.se*t+a.fi => x=a.se*t+a.fi(mod lcm)끝!
pint crt(pint a,pint b){
	if(a==pint{-1,-1} or b==pint{-1,-1})return{-1,-1};
	if(a.fi>b.fi)swap(a,b);
	auto [g,y1,y2]=xgcd(a.se,b.se);while(y1<0)y1+=b.se/g;
	int l=a.se/g*b.se,mul=(b.fi-a.fi)/g;
	if(mul*g!=b.fi-a.fi)return{-1,-1};
	y1*=mul,y2*=mul;
	return{(a.se*y1+a.fi)%l,l};
}

void discrete_log(){}  // baby step giant step
void discrete_sqrt(){}  // tonelli-shanks

//Author: anachor(https://judge.yosupo.jp/submission/39301)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"
namespace Rho{
	typedef long long LL;
	typedef unsigned long long ULL;
	ULL mult(ULL a,ULL b,ULL mod){
		LL ret=a*b-mod*(ULL)(1.0L/mod*a*b);
		return ret+mod*(ret<0)-mod*(ret>=(LL)mod);
	}
	ULL power(ULL x,ULL p,ULL mod){
		ULL s=1,m=x;
		while(p){
			if(p&1)s=mult(s,m,mod);
			p>>=1,m=mult(m,m,mod);
		}
		return s;
	}
	vector<LL> bases={2,325,9375,28178,450775,9780504,1795265022};
	bool isprime(LL n){
		if(n<2)return 0;
		if(n%2==0)return n==2;
		ULL s=__builtin_ctzll(n-1),d=n>>s;
		for(ULL x:bases){
			ULL p=power(x%n,d,n),t=s;
			while(p!=1&&p!=n-1&&x%n&&t--)p=mult(p,p,n);
			if(p!=n-1&&t!=s)return 0;
		}
		return 1;
	}
	///Binary gcd algo,optional. if omitted use __gcd
	ULL gcd(ULL u,ULL v){
		if(u==0)return v;
		if(v==0)return u;
		int shift=__builtin_ctzll(u|v);
		u>>=__builtin_ctzll(u);
		do{
			v>>=__builtin_ctzll(v);
			if(u>v)swap(u,v);
			v=v-u;
		} while(v);
		return u << shift;
	}
	///Returns a proper divisor if n is composite, n otherwise
	ULL FindFactor(ULL n){
		if(n==1||isprime(n))return n;
		ULL c=1,x=0,y=0,t=0,prod=2,x0=1,q;
		auto f=[&](ULL X){return mult(X,X,n)+c;};
		while(t++%40 or gcd(prod,n)==1){
			if(x==y)c=_rng()%(n-1)+1,x=x0,y=f(x);
			if((q=mult(prod,max(x,y)-min(x,y),n)))prod=q;
			x=f(x),y=f(f(y));
		}
		return gcd(prod,n);
	}
	///Returns all prime factors
	vector<ULL> factorize(ULL x){
		if(x==1) return{};
		ULL a=FindFactor(x),b=x/a;
		if(a==x) return{a};
		vector<ULL> L=factorize(a),R=factorize(b);
		L.insert(L.end(),R.begin(),R.end());
		return L;
	}
}
#pragma GCC diagnostic pop
