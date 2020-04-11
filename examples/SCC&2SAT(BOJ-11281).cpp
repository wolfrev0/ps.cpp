#include "Core.h"
#include "DirectedGraph.h"

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(11);
	srand((unsigned)time(0));

	int n, m;
	cin>>n>>m;
	DirectedGraph g(n*2);
	hfor(i, 0, m){
		int a, b;
		cin>>a>>b;
		g.add_edge((abs(a)-1)*2+(a<0), (abs(b)-1)*2+!(b<0));
		g.add_edge((abs(b)-1)*2+(b<0), (abs(a)-1)*2+!(a<0));
	}

	auto scc = g.scc().first;
	vector<int> tmp(n*2, -1);
	hfor(i, 0, scc.size()){
		for(auto& j:scc[i]){
			tmp[j]=i;
			if(tmp[j/2*2]==tmp[j/2*2+1]){
				cout<<0<<endl;
				return 0;
			}
		}
	}
	vector<int> val(n, -1);
	hfor(i, 0, scc.size()){
		bool v;
		if(val[scc[i].back()/2]==-1)
			v=false;
		else
			v=val[scc[i].back()/2] ^ scc[i].back()%2;
		for(auto& j:scc[i]){
				val[j/2]=j%2?!v:v;
		}
	}
	cout<<1<<endl;
	for(const auto& i:val)
		cout<<i<<' ';
	cout<<endl;
	return 0;
}
