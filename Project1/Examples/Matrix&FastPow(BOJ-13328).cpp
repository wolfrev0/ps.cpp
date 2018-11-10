#include "Core.h"
#include "Matrix.h"
#include "ModNum.h"

//have to change Core.h !!!
//"const int mod = int(1e9+7);" to
//"const int mod = int(31991);"

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	int d, t;
	cin >> d >> t;

	SqMat<ModNum> m(d);
	forh(i, 0, d)
	{
		m.arr[0][i] = 1;
		forh(j, 0, d)
		{
			if (i - j == 1)
				m.arr[i][j] = 1;
		}
	}
	m = fastpow(m, t);
	Mat<ModNum> v(d, 1);
	v.arr[0][0] = 1;
	auto ans = m * v;
	cout << ans.arr[0][0].val() << endl;

	return 0;
}