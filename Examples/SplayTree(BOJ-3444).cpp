#include "Core.h"
#include "SplayTree.h"
#define endl '\n'//do not use when solving interactive problem!!!

struct F{
	static int idT(){return int();}
	static bool idU(){return bool();}
	static int q(const int& a, const int& b) {return a+b; }
	static void upd(SplayNode<int, bool>* x) {swap(x->l, x->r);}
	static bool propa(const bool& clazy, const bool& lazy) { return clazy ^ lazy; }
};

struct Solver:public SplayTree<int, bool, F>{
	using P=SplayTree<int,bool,F>;
	using typename P::Node;
	Solver(){}

	void insert(int ord, int val){
		P::insert(ord, val);
		nodes.push_back({val, splay(ord+1)});
	}

	int getidx(int i){return order_of(nodes[i].second);}

	vector<pair<int,Node*>> nodes;
};

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(11);
	srand((u32)time(0));

	while(true){
		int n;
		cin>>n;
		if(!n)
			break;
		Solver s;
		forh(i, 0, n){
			int x;
			cin>>x;
			s.insert(i, x-1);
		}
		stable_sort(s.nodes.begin(), s.nodes.end(), [](auto& a, auto& b){return a.first<b.first;});
		forh(i,0,n){
			int idx=s.getidx(i);
			cout<<idx+1<<' ';
			s.update(i, idx+1, true);
		}
		cout<<endl;
	}

	return 0;
}