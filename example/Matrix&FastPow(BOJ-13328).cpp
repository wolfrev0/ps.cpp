#include "Core.h"
#include "Matrix.h"
#include "ModNum.h"

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((unsigned)time(0));

	mod=31991;
	int d, t;
	cin >> d >> t;

	Mat<ModNum, 50> m;
	hfor(i,0,d){
		m.a[0][i]=1;
		hfor(j, 0, d)
			if (i-j == 1)
				m.a[i][j] = 1;
	}
	m = fastpow(m, t);
	array<ModNum, 50> v={1};
	auto ans = m*v;
	cout << ans[0] << endl;

	return 0;
}