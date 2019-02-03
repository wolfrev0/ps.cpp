#include "Core.h"
#include "RegularNumber.h"
#include "SplayTree.h"
#define endl '\n'//do not use when solving interactive problem!!!

struct A{
	static A zero(){return {I32::inf(), -1, 0};}
	i64 m,M,s;
	bool operator==(const A& r)const{return m==r.m && M==r.M && s==r.s;}
	A operator+(const A& r)const{return {min(m, r.m), max(M, r.M), s+r.s};}
};

struct Solver:public SplayTree<A, Bool>{
	using Node = SplayTree<A, Bool>::Node;
	Solver():SplayTree<A, Bool>(0, [](const auto& a, const auto& b){return a+b;}, [](Node* x){if(x->lazy) swap(x->l, x->r);}, [](const auto& a, const auto& b){return a^b;}){}

	Node* find_by_order(int ord){
		splay(++ord);
		return root; 
	}

	int order_of(Node* x){
		splay(x);
		return size(x->l);
	}
};

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(11);
	srand((u32)time(0));

	int n, q;
	cin>>n>>q;
	Solver st;
	forh(i, 0, n)
		st.insert(i, {i+1,i+1,i+1});
	Solver::Node* arr[300001]={nullptr,};
	forh(i, 0, n)
		arr[i+1]=st.find_by_order(i);
	forh(i, 0, q){
		int op;
		cin>>op;
		if(op==1){
			int l, r;
			cin>>l>>r;
			l--, r--;
			auto res = st.query(l, r+1);
			cout<<res.m<<' '<<res.M<<' '<<res.s<<endl;
			st.update(l, r+1, true);
		}
		else if(op==2){
			int l, r, x;
			cin>>l>>r>>x;
			l--, r--;
			auto res = st.query(l, r+1);
			cout<<res.m<<' '<<res.M<<' '<<res.s<<endl;
			//st.shift(l, r+1, x);
			int len = r+1-l;
			x=(x%len+len)%len;
			if(x){
				st.update(l, r+1, true);
				st.update(l+x, r+1, true);
				st.update(l, l+x, true);
			}
		}
		else if(op==3){
			int x;
			cin>>x;
			x--;
			cout<<st.query(x).s<<endl;
		}else{
			int x;
			cin>>x;
			cout<<st.order_of(arr[x])<<endl;
		}
	}
	forh(i, 0, st.size()){
		cout<<st.query(i).s<<' ';
	}
	cout<<endl;

	return 0;
}