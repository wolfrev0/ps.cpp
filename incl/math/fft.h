#pragma once
#include "core/base.h"

using C=complex<fp>;

Arr<C> toC(const Arr<i64>& a){
	Arr<C> ret;
	for(auto i:a)ret.emplace_back(C(i,0));
	return ret;
}

Arr<i64> toInt(const Arr<C>& a){
	Arr<i64> ret;
	for(auto i:a)ret.emplace_back((int)round(i.real()));
	return ret;
}

// Arr<C> fft(const Arr<C>& a,C w){
// 	int n=sz(a);
// 	if(n==1)
// 		return a;
// 	Arr<C> ev(n/2),od(n/2),ret(n);
// 	forh(i,0,n)
// 		(i%2?od:ev)[i/2]=a[i];
// 	ev=fft(ev,w*w);od=fft(od,w*w);
// 	auto wi=C(1,0);
// 	forh(i,0,n){
// 		ret[i]=ev[i%(n/2)]+wi*od[i%(n/2)];
// 		wi*=w;
// 	}
// 	return ret;
// }
// Arr<C> fft(const Arr<C>& a){return fft(a,pow(exp(1),
// C(0,1)*(-2*pi/sz(a))));}

Arr<C> fft(Arr<C> a){
	int n=sz(a);
	for(int i=1,j=0;i<n;i++){
		int bit=n/2;
		while(!((j^=bit)&bit))bit/=2;
		if(i<j)swap(a[i],a[j]);
	}
	for(int i=1;i<n;i*=2){
		fp x=-pi/i;
		C w(cos(x),sin(x));
		for(int j=0;j<n;j+=i*2){
			C th(1,0);
			for(int k=0;k<i;k++){
				C tmp=a[i+j+k]*th;
				a[i+j+k]=a[j+k]-tmp;
				a[j+k]+=tmp;
				th*=w;
			}
		}
	}
	return a;
}

Arr<C> ffti(Arr<C> a){
	int n=sz(a);
	reverse(a.begin()+1,a.end());
	auto r=fft(a);
	for(auto& x:r)x/=C(n,0);
	return r;
}

Arr<i64> conv(const Arr<i64>& a,const Arr<i64>& b){
	auto fa=fft(toC(a));
	auto fb=fft(toC(b));
	Arr<C> fc;
	for(int i=0;i<sz(a);i++)fc.emplace_back(fa[i]*fb[i]);
	return toInt(ffti(fc));
}

// c[i]=sigma(j=0~i,a[j]*b[i-j])
Arr<i64> conv_mul(Arr<i64> a,Arr<i64> b){
	int n=1<<clg2(max(sz(a),sz(b))*2);
	a.resize(n),b.resize(n);
	return conv(a,b);
}

// c[i]=sigma(j=0~n-1,a[j]*b[i-j])
Arr<i64> conv_cir(Arr<i64> a,Arr<i64> b){
	int n=max(sz(a),sz(b)),m=1<<clg2(n*2);
	a.resize(m);
	reverse(b.begin(),b.end());
	for(int i=n;i<m;i++)b.emplace_back(b[(n+i)%n]);
	reverse(b.begin(),b.end());
	auto res=conv(a,b);
	rotate(res.begin(),res.end()-n,res.end());
	return res;
}

void ntt(){}
void walsh_hadamard(){}