#include "Core.h"
#include "LCA.h"
#define endl '\n'//do not use when solving interactive problem!!!

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((u32)time(0));

	int n;
	cin>>n;
	Tree<int> t(n);
	forh(i, 0, n-1){
		int a, b;
		cin>>a>>b;
		a--, b--;
		t.add_edge(a,b,1);
	}
	LCA<int> rt(t, 0);
	int m;
	cin>>m;
	forh(i, 0, m){
		int	a, b;
		cin>>a>>b;
		a--,b--;
		cout<<rt.lca(a, b)+1<<endl;
	}

	return 0;
}