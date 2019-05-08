#include "Core.h"
#include "SimpleGraph.h"

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(11);
	srand((unsigned)time(0));

	int n;
	cin>>n;
	Graph<int> g(n);
	while(true){
		int a,b;
		cin>>a>>b;
		if(a<0&&b<0)
			break;
		a--,b--;
		g.add_edge(a,b,1, false);
	}
	vector<vector<vector<int>>> memo(n, {(uint)n, vector<int>(n, -1)});
	vector<pair<int,int>> tmp;
	forh(i, 0, n){
		int val = 0;
		forh(j, 0, n){
			if(i==j)
				continue;
			val = max(val, g.floyd(i, j, 0, memo));
		}
		tmp.push_back({val, i});
	}
	sort(tmp.begin(), tmp.end());
	int score=tmp[0].first;
	vector<int> ans;
	int i=0;
	while(i<n && tmp[i].first == score)
		ans.push_back(tmp[i++].second);
	cout<<score<<' '<<ans.size()<<endl;
	for(auto i:ans)
		cout<<i+1<<' ';
	cout<<endl;

	return 0;
}