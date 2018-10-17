#include "Matrix.h"
#include "NumberTheory.h"

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	cout << fastpow(1, 1) << endl;
	cout << fastpow(1.0, 1) << endl;

	int n, k;
	cin >> n >> k;
	Mat v(20, 1);
	forh(i, 0, n)
		cin >> v.arr[i][0], cin.get();
	SqMat m(20);
	forh(i, 0, 20)
		m.arr[i][i] = -1;
	forh(i, 0, 20 - 1)
		m.arr[i][i + 1] = 1;
	auto tmp = fastpow(m, k)*v;
	forh(i, 0, n - k - 1)
		cout << tmp.arr[i][0] << ',';
	cout << tmp.arr[n - k - 1][0] << endl;

	return 0;
}