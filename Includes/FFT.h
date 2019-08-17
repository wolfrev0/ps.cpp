#pragma once
#include "Core.h"

using C=complex<f64>;

//ceil(log(n))
int lgc(i64 n, int base=2) {
	int ret=0;
	int rem=0;
	while (n)
		rem+=n%base, n/=base, ret++;
	return ret-(rem<=1);
}

arr<C> toC(const arr<i64>& a){
	arr<C> ret;
	for(auto i:a)
		ret.pb(C(i,0));
	return ret;
}

arr<i64> toi(const arr<C>& a){
	arr<i64> ret;
	for(auto i:a)
		ret.pb(round(i.real()));
	return ret;
}

const auto ee=exp(1);

arr<C> fft(const arr<C>& a, C w){
	int n=sz(a);
	if(n==1)
		return a;
	arr<C> ev(n/2), od(n/2), ret(n);
	hfor(i,0,n)
		(i%2?od:ev)[i/2]=a[i];
	ev=fft(ev,w*w); od=fft(od,w*w);
	auto wi=C(1,0);
	hfor(i,0,n){
		ret[i]=ev[i%(n/2)]+wi*od[i%(n/2)];
		wi*=w;
	}
	return ret;
}
arr<C> fft(const arr<C>& a){return fft(a, pow(ee, C(0,1)*(-2*pi/sz(a))));}

// //topology's no-recursion code
// arr<C> fft(arr<C> a){
// 	int n=sz(a);
// 	for(int i=1,j=0;i<n;i++) {
// 		int bit=n/2;
// 		while(!((j^=bit)&bit))bit/=2;
// 		if(i<j)swap(a[i],a[j]);
// 	}
// 	for(int i=1;i<n;i*=2) {
// 		f64 x=-pi/i;
// 		C w(cos(x),sin(x));
// 		for(int j=0;j<n;j+=i*2) {
// 			C th(1,0);
// 			for (int k=0;k<i;k++) {
// 				C tmp=a[i+j+k]*th;
// 				a[i+j+k]=a[j+k]-tmp;
// 				a[j+k]+=tmp;
// 				th *= w;
// 			}
// 		}
// 	}
// 	return a;
// }

arr<C> ffti(arr<C> a){
	int n=sz(a);
	reverse(a.begin()+1, a.end());
	return mapp(fft(a), [n](auto x){return x/C(n,0);});
}

arr<i64> conv(const arr<i64>& a, const arr<i64>& b){
	const auto& fa=fft(toC(a));
	const auto& fb=fft(toC(b));
	arr<C> fc;
	hfor(i,0,sz(a)) fc.pb(fa[i]*fb[i]);
	return toi(ffti(fc));
}

arr<i64> conv_mul(arr<i64> a, arr<i64> b){
	int n=1<<lgc(max(sz(a), sz(b))*2);
	a.resize(n);
	b.resize(n);
	return conv(a,b);
}

arr<i64> conv_cir(arr<i64> a, arr<i64> b){
	int n=max(sz(a), sz(b));
	int m=1<<lgc(n*2);
	a.resize(m);
	reverse(all(b));
	hfor(i,n,m)
		b.pb(b[(n+i)%n]);
	reverse(all(b));
	auto res=conv(a,b);
	return {res.end()-n, res.end()};
}