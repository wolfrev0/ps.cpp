#pragma once
#include "core/base.h"
#include "misc/i128.h"

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
int modinv(int n,int m){auto [g,x,y]=xgcd(n,m); assert(g==1); while(x<0)x+=m; return x;}

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
//출처불명
Arr<i64> pollard_rho(i64 n){
	func(i64,rho,i64 n){
		while(true){
			i64 x=rand()%(n-2)+2;
			i64 y=x,c=rand()%(n-1)+1;
			while(true){
				x=(i128(x)*x%n+c)%n;
				y=(i128(y)*y%n+c)%n;
				y=(i128(y)*y%n+c)%n;
				i64 d=gcd(abs(x-y),n);
				if(d==1) continue;
				if(!miller_rabin(d)){n=d;break;}
				else return d;
			}
		}
	};
	Arr<i64> v;
	while(~n&1)n>>=1,v.push_back(2);
	if(n==1) return v;
	while(!miller_rabin(n)){
		i64 d=rho(n);
		while(n%d==0) v.push_back(d),n/=d;
		if(n==1) break;
	}
	if(n!=1) v.push_back(n);
	return v;
}

int lucas(int n, int m, int p){
	Arr<int> fac(p),inv(p*2);
	fac[0]=1;
	for(int i=1;i<p;i++)
		fac[i]=fac[i-1]*i%p;
	inv[p-1]=p-1;//willson
	for(int i=p-2;~i;i--)
		inv[i]=inv[i+1]*(i+1)%p;
	int ret=1;
	while(n||m){
		ret = ret*fac[n%p]%p*inv[m%p]%p*inv[n%p-m%p]%p;
		n/=p,m/=p;
	}
	return ret;
}

//chinese remainder theorem
//https://rkm0959.tistory.com/180?category=828364
//merge two equation [ x=a.fi (mod a.se), x=b.fi (mod b.se) ]
//these are equivalent with
//x=a.se*y+a.fi=b.fi (mod b.se)
//=> a.se*y1+b.se*y2=b.fi-a.fi
//=> 이제 xgcd로 y1,y2 구할 수 있다. 정확히는 y1=t(mod b.se/g)를 알수있다.
//=> 위와 동치인 y1=t+b.se/g*m을 x=a.se*y1+a.fi에 대입하면
//=> x=a.se*b.se/g*m+a.se*t+a.fi => x=a.se*t+a.fi (mod lcm) 끝!
pint crt(pint a, pint b){
	if(a==pint{-1,-1} or b==pint{-1,-1})return {-1,-1};
	if(a.fi>b.fi)swap(a,b);
	auto [g,y1,y2]=xgcd(a.se,b.se);while(y1<0)y1+=b.se/g;
	int l=a.se/g*b.se, mul=(b.fi-a.fi)/g;
	if(mul*g!=b.fi-a.fi)return {-1,-1};
	y1*=mul,y2*=mul;
	return {(a.se*y1+a.fi)%l,l};
}

void discrete_log() {}  // baby step giant step
void discrete_sqrt() {}  // tonelli-shanks