#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;

//Don't use at interactive problem
// #define endl '\n'

#define FP_EPS 1e-11
#define COUT_FP 12
// #define CPP20
//Arr
template<class T, class P=conditional_t<is_same<bool,T>::value,deque<T>,vector<T>>>
struct Arr:public P{
	Arr():Arr(0){}
	Arr(int n,T init=T()):P(n,init){}
	Arr(initializer_list<T>il):P(il){}
#ifdef CPP20
	Arr(auto its, auto ite):P(its,ite){}
#endif
	T& operator[](int i){
		#if DEBUG
		static bool _z=false;
		if(i<0&&!_z)_z=true,cerr<<"[INFO] Negative Index Found"<<endl;
		#endif
		return P::operator[](i>=0?i:i+this->size());
	}
	const T& operator[](int i)const{return P::operator[](i>=0?i:i+this->size());}
	T& at(int i){return *this[i];}
	const T& at(int i)const{return *this[i];}
};
template<class... A> auto ARR(auto n,A&&... a)
{if constexpr(!sizeof...(a)) return n; else return Arr(n,ARR(a...));}

#define int i64
#define pushb push_back
#define pushf push_front
#define popb pop_back
#define popf pop_front
#define empl emplace
#define emplb emplace_back
#define emplf emplace_front
#define fi first
#define se second
#define mkp make_pair
#define mkt make_tuple
#define cxp constexpr
#define lb lower_bound
#define ub upper_bound
#define reduce accumulate
using i64=long long;using u64=unsigned long long;using f64=double;
using pint=pair<int,int>;using tint=tuple<int,int,int>;
template<class T>using Str=basic_string<T>;

//Handy Funcs
template<class T>int sz(const T& x){return x.size();}
template<class T>cxp T inf(){return numeric_limits<T>::max()/2;}
int divc(int a,int b){if(b<0)a=-a,b=-b;return (a>0)?(a+b-1)/b:a/b;}
int divf(int a,int b){if(b<0)a=-a,b=-b;return (a>0)?a/b:(a-b+1)/b;}
cxp int lg2f(int x){return 63-__builtin_clzll(x);}
cxp int lg2c(int x){return 64-__builtin_clzll(x-1);}
template<class T>inline T sq(T x){return x*x;}
bool assmin(auto& a,auto&& b){return a>b?a=b,true:false;}
bool assmax(auto& a,auto&& b){return a<b?a=b,true:false;}
int argmin(const auto& a){return min_element(a.begin(),a.end())-a.begin();}
int argmax(const auto& a){return max_element(a.begin(),a.end())-a.begin();}

//Monoid
#ifdef CPP20
template<class T, auto _f=[](T x,T y){return x+y;}, T _id=0>
struct Monoid{static cxp auto f=_f,id=_id;};
template<class T, class M=Monoid<T>>
Arr<T> cumf(const Arr<T>& a){
	Arr<T> b(sz(a)+1,M::id);
	for(int i=0;i<sz(a);i++)
		b[i]=M::f(b[i-1],a[i]);
	return b;
}
#endif

//Func Exts
#define RETT(...) __VA_ARGS__
#define func(RetT,fname,...) function<RetT(__VA_ARGS__)> fname=[&](__VA_ARGS__)->RetT
#define lam(expr,...) [&](__VA_ARGS__){return expr;}

#define PQ std::priority_queue
template<class T>using PQMax=PQ<T>;
template<class T>using PQMin=PQ<T,vector<T>,greater<T>>;

//Consts
const f64 pi=acosl(-1),eps=FP_EPS;
const int dir[4][2]={{1,0},{0,1},{-1,0},{0,-1}};

//Pre-runs
#if !(DEBUG)
auto __PR1=(ios::sync_with_stdio(0),cin.tie(0),cout.tie(0));
#endif
auto& __PR2=(cout<<fixed<<setprecision(COUT_FP));
//

// Random
mt19937 _rng(i64(new int) ^ time(0));
int rd() {
	static uniform_int_distribution<int> dist(0, inf<int>());
	return dist(_rng);
}
int rd(int e) { return rd() % e; }
int rd(int s, int e) { return rd() % (e - s) + s; }
f64 rdf() {
	static uniform_real_distribution<f64> dist(0, 1);
	return dist(_rng);
}
void shuffle(auto is, auto ie) { shuffle(is, ie, _rng); }

void solve(){
	int n; cin>>n;

	func(Arr<int>,get,int x){
		cout<<"? "<<x+1<<endl;
		Arr<int> ret(n,0);
		for(auto& i:ret)
			cin>>i;
		return ret;
	};
	set<pint> g;
	func(void,add,int x,int y){g.empl(min(x,y),max(x,y));};

	auto d=get(0);
	int c[2]{};
	for(int i=1;i<n;i++){
		c[d[i]%2]++;
		if(d[i]==1)
			add(0,i);
	}
	if(c[0]<c[1]){
		for(int i=1;i<n;i++){
			if(d[i]%2==0){
				auto di=get(i);
				for(int j=0;j<n;j++)
					if(di[j]==1)
						add(i,j);
			}
		}
	}else{
		for(int i=1;i<n;i++){
			if(d[i]%2){
				auto di=get(i);
				for(int j=0;j<n;j++)
					if(di[j]==1)
						add(i,j);
			}
		}
	}
	cout<<"!"<<endl;
	for(auto i:g)
		cout<<i.fi+1<<' '<<i.se+1<<endl;
}
signed main(){
	// int ti=0,t=cin.tok();
	// while(++ti<=t)
	// 	cout<<"Case #"<<ti<<": ",
		solve();
}
