#include "Core.h"
#include "String.h"

char text[1000010];
char pattern[1000010];

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((unsigned)time(0));

	cin.getline(text, 1000010);
	cin.getline(pattern, 1000010);
	int len = strlen(pattern);
	auto res = kmp2(text, pattern);
	vector<int> ans;
	forh(i, 0, res.size())
		if(res[i]==len)
			ans.push_back(i-len+1);
	cout << ans.size() << endl;
	for(auto i:ans)
		cout<<i+1<<' ';

	return 0;
}