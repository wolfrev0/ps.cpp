#pragma once
#ifndef DEBUG 
	#pragma GCC optimize ("Ofast")
#endif
#include <bits/stdc++.h>

using namespace std;
using f64 = double;using i64=long long;using u64=unsigned long long;

#define hfor(var, s, e) for(int var=s; s<=var && var<e; ++var)//half-opened range
#define hfori(var, s, e) for(int var=e-1; s<=var && var<e; --var)//inversion
#define hforo(var, s, e) int var=s; for(; s<=var && var<e; ++var)//out declaration
#define hforoi(var, s, e) int var=e-1; for(; s<=var && var<e; --var)
#define cfor(var, s, e) hfor(var, s, (e)+1)//closed range
#define cfori(var, s, e) hfori(var, s, (e)+1)
#define cforo(var, s, e) hforo(var, s, (e)+1)
#define cforoi(var, s, e) hforoi(var, s, (e)+1)
#define rep(x) hfor(repi,0,x)
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb pop_back
#define pf push_front
#define ef pop_front
#define fi first
#define se second
#define gcd __gcd

template<typename T> constexpr T inf() { return numeric_limits<T>::max() / 2; }
auto mri(auto it){ return make_reverse_iterator(it); }//*mri(it) == *prev(it)
auto rerase(auto& c, auto ri){ return next(mri(c.erase(prev(ri.base())))); }
auto accumulate(auto a, auto b, int c=0){ return std::accumulate(a,b,i64(c)); }
auto sum(auto a, auto b){return accumulate(a,b);}
int sz(const auto& x){ return (int)x.size(); }
int rd(int lb, int ub){static mt19937 rng(time(0)^i64(new int)); return uniform_int_distribution<int>(lb, ub-1)(rng);}
int rd(int ub=inf<int>()){return rd(0,ub);}
#define random rd

const f64 pi=acos(-1), eps=1e-12;
const int prime=998244353;//1073741783 int(2e9+11) int(1e9+9)
const int mod=int(1e9+7);
auto ___=(ios::sync_with_stdio(0), cin.tie(0), cout.tie(0),(cout<<fixed<<setprecision(11)), srand((int)time(0)), 0);

//ceil(log(n))
int lgc(i64 n, int base=2) {
	int ret=0;
	int rem=0;
	while (n)
		rem+=n%base, n/=base, ret++;
	return ret-(rem<=1);
}

#define endl '\n'//not interactive?
//#define int i64//overflow?

int topow2(int n){return 1<<lgc(n);}

#define arr vector
using C=complex<double>;

arr<C> toC(const arr<int>& a){
	arr<C> ret;
	for(auto i:a)
		ret.pb(C(i,0));
	return ret;
}

arr<int> toi(const arr<C>& a){
	arr<int> ret;
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
	ev=fft(ev,w*w); od=fft(od, w*w);
auto t=C(1,0);
	hfor(i,0,n){
		ret[i]=ev[i%(n/2)]+t*od[i%(n/2)];
        t*=w;
    }
	return ret;
}

arr<C> ffti(const arr<C>& a){
	//reverse(a.begin()+1, a.end());
	//a대신 ret을 뒤집어도 된다.
	auto ret=fft(a, pow(ee, C(0,1)*(-2*pi/sz(a))));
	reverse(ret.begin()+1, ret.end());
	for(auto&i:ret)
        i/=sz(a);
	return ret;
}

arr<int> conv_tri(arr<int>& a, arr<int>& b){
	int n=sz(a), m=topow2(n*2);
	a.resize(m);
	b.resize(m);
    const auto& fa=fft(toC(a), pow(ee, C(0,1)*(-2*pi/m)));
	const auto& fb=fft(toC(b), pow(ee, C(0,1)*(-2*pi/m)));
	arr<C> fc(sz(a));
	hfor(i,0,sz(a))
        fc[i]=fa[i]*fb[i];
	auto res=toi(ffti(fc));
	return {res.begin(), res.begin()+n};
}

signed main(){
	int n;
	cin>>n;
	vector<int> a(200001);
    hfor(i,0,n){
int x;
        cin>>x;
a[x]++;
    }
int m;
cin>>m;
int b[200000];
    hfor(i,0,m)
        cin>>b[i];
    auto res=conv_tri(a,a);
int ans=0;
hfor(i,0,m)
ans+=res[b[i]]||a[b[i]];
	cout<<ans<<endl;

	return 0;
}
