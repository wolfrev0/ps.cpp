#include "Matrix.h"

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	int d, t;
	cin >> d >> t;

	SqMat m(d);
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
	Mat v(d, 1);
	v.arr[0][0] = 1;
	auto ans = m * v;
	cout << ans.arr[0][0] << endl;

	return 0;
}