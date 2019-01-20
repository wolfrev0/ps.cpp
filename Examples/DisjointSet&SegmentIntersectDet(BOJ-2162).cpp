#include "Core.h"
#include "Line.h"
#include "DisjointSet.h"

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((u32)time(0));

	int n;
	cin >> n;
	Segment<I64> arr[3000];
	forh(i, 0, n){
		Vec2<I64> s, e;
		cin >> s.x.a >> s.y.a >> e.x.a >> e.y.a;
		arr[i]=Segment{s, e};
	}
	DisjointSet djs(n);
	forh(i, 0, n) {
		forh(j, i + 1, n) {
			try {
				if (arr[i].intersect_det(arr[j]))
					djs.uni(i, j);
			}
			catch (const LineSame &e) {
				if (arr[i].s() > arr[j].e() || arr[i].e() < arr[j].s())
					;
				else
					djs.uni(i, j);
			}
		}
	}
	map<int, vector<int>> m;
	uint ans2 = 0;
	for (int i = 0; i < n; i++)
		m[djs.find(i)].push_back(i), ans2 = max(ans2, (uint)m[djs.find(i)].size());
	cout << m.size() << endl << ans2 << endl;


	return 0;
}