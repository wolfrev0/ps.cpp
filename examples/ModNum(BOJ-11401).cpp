#include "Core.h"
#include "ModNum.h"

i64 f(int n)
{
	i64 res = 1;
	forc(i, 1, n)
		res = res * i % mod;
	return res;
}

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((unsigned)time(0));

	int n, k;
	cin >> n >> k;
	ModNum mi1 = 1;	mi1 /= f(k);
	ModNum mi2 = 1; mi2 /= f(n - k);
	cout << (mi1*mi2*f(n)).val() << endl;

	return 0;
}