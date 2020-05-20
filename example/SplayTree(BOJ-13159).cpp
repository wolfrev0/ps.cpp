#include "Core.h"
#include "SplayTree.h"
#define endl '\n'//do not use when solving interactive problem!!!

struct A{
	i64 m=0x7fffffffffffffff/2, M=-1, s=0;
	bool operator==(const A& r)const{return m==r.m && M==r.M && s==r.s;}
	A operator+(const A& r)const{return {min(m, r.m), max(M, r.M), s+r.s};}
};

using Node = SplayNode<A, bool>;

struct F{
	static A q(const auto& a, const auto& b){return a+b;}
	static void upd(Node* x){if(x->lazy) swap(x->l, x->r);}
	static bool propa(const auto& a, const auto& b){return a^b;}
};

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(11);
	srand((unsigned)time(0));

	int n, q;
	cin>>n>>q;
	SplayTree<A, bool, F> st;
	hfor(i, 0, n)
		st.insert(i, {i+1,i+1,i+1});
	Node* arr[300001]={nullptr,};
	hfor(i, 0, n)
		arr[i+1]=st.find_by_order(i);
	hfor(i, 0, q){
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
			cout<<st.order_of(arr[x])+1<<endl;
		}
	}
	hfor(i, 0, st.size()){
		cout<<st.query(i).s<<' ';
	}
	cout<<endl;

	return 0;
}