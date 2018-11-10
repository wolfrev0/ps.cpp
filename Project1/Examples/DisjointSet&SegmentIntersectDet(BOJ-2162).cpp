#include "Core.h"
#include "Line.h"
#include "DisjointSet.h"

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	int n;
	cin >> n;
	Segment arr[3000];
	forh(i, 0, n)
		cin >> arr[i].s.x >> arr[i].s.y >> arr[i].e.x >> arr[i].e.y;
	DisjointSet djs(n);
	forh(i, 0, n) {
		forh(j, i + 1, n) {
			try {
				if (arr[i].intersect(arr[j]) != err)
					djs.uni(i, j);
			}
			catch (const LineSame &e) {
				auto li = arr[i], lj = arr[j];
				if (arr[i].s > arr[j].e || arr[i].e < arr[j].s)
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