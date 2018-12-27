#include "Xset.h"

int main()
{
	cin.sync_with_stdio(false), cin.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	int n;
	int arr[200001];
	vector<pair<int,int>> v;
	cin >> n;
	forh(i, 0, n)
	{
		cin >> arr[i];
		arr[i] = min(arr[i], n)-1;
		v.push_back({arr[i], i});
	}
	sort(v.begin(), v.end(), [](auto &a, auto &b){return min(a.first, a.second-1) < min(b.first, b.second-1); });

	ull a = 0;
	xmultiset<int> s;
	vector<int> q;
	forh(i, 0, n){
		if(!i || min(v[i-1].first, v[i-1].second-1) < min(v[i].first, v[i].second-1)){
			for(auto j:q)
				s.insert(j);
			q.clear();
		}
		a+=s.size()-s.order_of_key(v[i].second-1);
		q.push_back(v[i].first);
	}
	cout<<a<<endl;

	return 0;
}