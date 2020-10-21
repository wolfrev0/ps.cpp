#pragma once
#include "Core.h"

//Berlekamp Massey
//NOTE: Linear Recurrence Sequence의 점화식 도출은 행렬형태로 표현해서 O(n^3)가능할듯 한데,
//Berlekamp Massey는 O(n^2)이다.
//NOTE: f(n)=a*f(n-i)+b*f(n-j)+.. 꼴이 아니라 f(n)+a*f(n-i)+b*f(n-j)+...=0꼴으로 반환한다.
template<int mod=int(1e9+7)>
Arr<int> guess(Arr<int> seq){
	Func<int(int,int)> qp=[&](int x, int p){
		if(!p) return 1ll;
		int z=qp(x,p/2);
		return z*z%mod*(p%2?x:1)%mod;
	};
	
	for(auto& i:seq)i=(i%mod+mod)%mod;
	//b: best(=shortest) relation so far
	//c: current relation
	Arr<int> b={1},c={1};
	//bi: pos of b
	//bd: delta of b
	int bi,bd;
	rep(i,sz(seq)){
		int v=0;//evaluated value at i
		rep(j,sz(c))
			v=(v+c[j]*seq[i-j])%mod;
		if(!v)continue;//good
		if(sz(c)==1){//first non-zero pos
			c.pushb(0), bi=i, bd=v;
			continue;
		}
		int coef=v*qp(bd,mod-2)%mod;
		Arr<int> a(i-bi);//add zeroes in front
		for(auto j:b)
			a.pushb((-coef+mod)*j%mod);
		if(sz(c)>sz(a))
			a.resize(sz(c));
		rep(j,sz(c))
			a[j]=(a[j]+c[j])%mod;
		if(sz(c)<=i-bi+sz(b))
			b=c, bi=i, bd=v;
		c=a;
	}
	return c;
}

//O(M^2logN). https://codeforces.com/blog/entry/61306 might help to understand.
//can be improved to O(MlogMlogN). see https://algoshitpo.github.io/2020/05/20/linear-recurrence/
template<int mod=int(1e9+7)>
int calc_nth(Arr<int> seq, Arr<int> rec, int n){
	int z=0;
	while(z<sz(rec) and !rec[sz(rec)-1-z])z++;
	if(n<z) return seq[n];
	seq.erase(seq.begin(),seq.begin()+z);
	rec.erase(rec.end()-z, rec.end());
	n-=z;

	auto mul=[&](const Arr<int>& a, const Arr<int>& b){
		Arr<int> c(sz(a)+sz(b)-1);
		rep(i,sz(a))
			rep(j,sz(b))
				c[i+j]=(c[i+j]+a[i]*b[j])%mod;
		
		//mod by rec
		//NOTE: rec's MSB==1
		//NOTE: rec is reversed
		hfori(i,sz(rec)-1,sz(c))
			repi(j,sz(rec))
				c[i-j]=(c[i-j]-c[i]*rec[j]%mod+mod)%mod;
		while(sz(c) and !c.back())c.popb();
		return c;
	};
	Func<Arr<int>(const Arr<int>&,int)> qp=[&](const Arr<int>& x, int p){
		if(!p) return Arr<int>{1};
		auto z=qp(x,p/2);
		return mul(mul(z,z),p%2?x:Arr<int>{1});
	};
	auto coef=qp({0,1},n);
	int r=0;
	rep(i,sz(coef))
		r=(r+coef[i]*seq[i]%mod+mod)%mod;
	return r;
}
