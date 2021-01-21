#pragma once
#include "Core.h"

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
Arr<int> sieve_eutot(int n){return{};}
void discrete_log(){}//baby step giant step
bool miller_rabin(i64 n){return true;}

/////////////////////////////
//From Here: Snippet Exists//
/////////////////////////////
int log_f(i64 n, int base=2){int ret=0; while(n)n/=base,ret++; return ret-1;}
int log_c(i64 n, int base=2) {int ret=0,rem=0; while(n)rem+=n%base,n/=base,ret++; return ret-(rem<=1);}
int sqrt_f(i64 n){i64 i=1; while(i*i<=n)i++; return i-1;}
int sqrt_c(i64 n){i64 i=1; while(i*i<n)i++; return i;}
template<class T>T fp(const T& a, int p){ if(!p)return T(1); T z=fp(a, p/2); return z*z*(p%2?x:1); }
template<class T> Arr<T> factorials(int n){Arr<T>r(n,1); forh(i,1,n)r[i]=r[i-1]*i; return r;}
template<class T, int n, int k>Arr<Arr<T>> binoms(){Arr<Arr<T>> r(n, Arr<T>(k));forh(i,1,n){r[i][0]=1;forh(j,1,k)r[i][j]=r[i-1][j-1]+r[i-1][j];}return r;}
//<Adjust Formaula>
//xgcd(a,b) solves ax+by=gcd(a,b)=g
//ax+by=c satisfied iff c=g*k     so, do x*=k and y*=k.
//if (x,y) is one of root, (x+t*b/g, y-t*a/g) is also root.(t is arbitary integer)
//when x,y have boundary, see (jung2381187, koosaga)'s code at boj_11661, linearity?
//<Multivariable Linear Deophantine>
//ax+by+cz=k => gcd(a,b)w+cz=k && ax+by=gcd(a,b)w (extend it recursively)
tint xgcd(i64 a,i64 b){ if(!b)return{a,1,0}; auto[g,x,y]=xgcd(b,a%b); return{g,y,x-(a/b)*y}; }

//whatelse can be sieved? sieve_numdiv, sieve_sumdiv, etc.
Arr<bool> sieve_primes(int n){Arr<bool>s(n,1);s[0]=s[1]=0; for(i64 i=2;i*i<n;i++){if(!s[i])continue;for(i64 j=i*i;j<n;j+=i)s[j]=0;}return s;}
Arr<Arr<int>> sieve_divs(int n){Arr<Arr<int>>r(n);forh(i,1,n){for(int j=i;j<n;j+=i)r[j].emplb(i);}return r;}

Arr<i64> divs(i64 n){ Arr<i64> r,s; for(i64 i=1;i*i<=n;i++) if(n%i==0){r.emplb(i);if(i!=n/i)s.emplb(n/i);}reverse(all(s));r.insert(r.end(),all(s));return r;}
Arr<i64> facts(i64 n){ i64 c=n;Arr<i64> r; for(i64 i=2;i*i<=n;i++) while(!(c%i)){c/=i;r.emplb(i);} if(c>1)r.emplb(c); return r; }
Arr<int> primes(int n){auto s=sieve_primes(n);Arr<int>r;rep(i,n)if(s[i])r.emplb(i);return r;}
int eutot(int n){int r=1,x=n;for(int i=2;i*i<=n;i++){if(x%i)continue;while(x%i==0)x/=i,r*=i;r=r/i*(i-1);}if(x>1)r*=x-1;return r;}