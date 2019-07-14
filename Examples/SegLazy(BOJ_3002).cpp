#include "Core.h"
#include "SegLazy.h"
#define endl '\n'//not interactive?
//#define int i64//overflow?

struct A{
	int cnt[10]{1,};
	constexpr A(){}
	A operator+(const A& r)const{
		A ret;
		hfor(i,0,10)
			ret.cnt[i]=cnt[i]+r.cnt[i];
		return ret;
	}
	A shift(int n)const{
		A ret;
		hfor(i,0,10)
			ret.cnt[i]=cnt[(i-n%10+10)%10];
		return ret;
	}
	int get(){
		int ret=0;
		hfor(i,0,10)
			ret+=i*cnt[i];
		return ret;
	}
};

struct B:public SegLazy<A, int>{
	B(int n):SegLazy<A, int>(n){}
	A fq(const A& a, const A& b)override{return a+b;}
	A fupd(const A& a, const int& b, signed c)override{return a.shift(b);}
	int fpropa(const int& a, const int& b)override{return a+b;}	
};

signed main(){
	//README: need c++2a compile option.
	//I believe you. You can fix it to c++17.
	int n, m;
	cin>>n>>m;
	string s;
	cin>>s;
	B st(n);
	hfor(i,0,n)
		st.upd(i, s[i]-'0');
	hfor(i,0,m){
		int a,b;
		cin>>a>>b;
		a--,b--;
		cout<<st.q(a,b+1).get()<<endl;
		st.upd(a, b+1, 1);
	}
	
	return 0;
}