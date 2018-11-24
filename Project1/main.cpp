#include "ModNum.h"

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	char buf[1000010];
	while (true)
	{
		cin.getline(buf, sizeof buf);
		if (string(buf) == ".")
			break;
		string p = buf;

		ModNum h = 0;
		ModNum pw = 1;
		forh(i, 0, p.size()) {
			h *= prime;
			pw *= prime;
			h += p[i];
		}
		auto t = h;
		forho(i, 0, p.size()) {
			h -= p[p.size() - 1 - i];
			h /= prime;
			t -= (pw /= prime) * p[i];
			if (h == t)
				break;
		}
		if (p.size() % (i + 1))
			cout << 1 << endl;
		else
			cout << p.size() / (i + 1) << endl;
	}

	return 0;
}