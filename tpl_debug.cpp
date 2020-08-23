#include "Core.h"
#include "FastIO.h"

#define endl '\n'//Interactive? Partial Score?
#define int i64//MLE?
using pint = pair<int,int>;
using tint = tuple<int,int,int>;
template<typename T>ostream& operator<<(ostream& s, const Arr<T>& a) {for(auto i:a) cout<<i<<' '; return s;}
auto cinint(){int x;cin>>x;return x;}
auto cinchr(){char x;cin>>x;return x;}
auto cinints(int n){Arr<int> a(n);for(auto&i:a)cin>>i;return a;}

template <class T, typename = void>
struct is_iterable : false_type {};
template <class T>
struct is_iterable<T, void_t<decltype(begin(declval<T>())), decltype(end(declval<T>()))>> : true_type {};

template<class A, class B, typename enable_if<!is_iterable<pair<A,B>>::value,int>::type = 0>
void print(const pair<A,B>& a, int d=0);
template<class TupType, size_t... I>
void print(const TupType& _tup, index_sequence<I...>, int d=0);
template<class... T>
void print (const tuple<T...>& _tup, int d=0);

template<class T, typename enable_if<!is_iterable<T>::value,int>::type = 0>
void print(const T& a, int d=0){cout<<a<<',';}
template<class T, typename enable_if<is_iterable<T>::value,int>::type = 0>
void print(const T& a, int d=0){
	static string ob="[{(", cb="]})";
	cout<<endl<<string(d,' ')+ob[d%sz(ob)];
	for(const auto& i:a)print(i,d+1);
	cout<<cb[d%sz(ob)];
}
template<class A, class B, typename enable_if<!is_iterable<pair<A,B>>::value,int>::type = 0>
void print(const pair<A,B>& a, int d){cout<<endl<<string(d,' ')+'<'; print(a.fi,d+1); print(a.se,d+1);cout<<'>';}
template<class TupType, size_t... I>
void print(const TupType& _tup, index_sequence<I...>, int d){cout<<endl<<string(d,' ')+'<'; (..., print(get<I>(_tup),d+1)); cout<<'>';}
template<class... T>
void print (const tuple<T...>& _tup, int d)
{print(_tup, make_index_sequence<sizeof...(T)>(), d);}

signed main(){
	print(ARR(2,2,2,2,2,0));
	print(ARR(2,3,"asdf"));
	map<int,set<Arr<string>>> a={
		{0,{{"123"},{"zzz"},{"asdf"}}},
		{4,{{"qwer"},{"ty"},{"xyz"}}},
	};
	print(a);
	print(mkp(3,"12"));
	print(mkt("123",21,1e3+4));
	Arr<tuple<int,string,double>> b;
	b.emplb(12,"asdf",1e3);
	b.emplb(8,"zz",-21);
	b.emplb(-2,"qwerty",34);
	print(b);
}
