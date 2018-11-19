#include "Core.h"
#include "String.h"

char text[1000010];
char pattern[1000010];

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	cin.getline(text, 1000010);
	cin.getline(pattern, 1000010);
	auto res = kmp2(text, pattern);
	cout << res.size() << endl;
	for (auto i : res)
		cout << i + 1 << ' ';

	return 0;
}