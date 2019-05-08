#include "Core.h"
#include "ModNum.h"
#include "NumberTheory.h"
#define endl '\n'//do not use when solving interactive problem!!!

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(11);
	srand((unsigned)time(0));

	int n, k;
	cin>>n>>k;
	cout<<binom(ModNum(n), ModNum(k))<<endl;

	return 0;
}