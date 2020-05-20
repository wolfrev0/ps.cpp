#include "Core.h"
#include "MonotonicQ.h"
#define endl '\n'//do not use when solving interactive problem!!!

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(11);
	srand((unsigned)time(0));

  int n, l;
	cin>>n>>l;
	MonotonicQ<int> q;
	hfor(i, 0, n){
		int x;
		cin>>x;
		q.push(x);
		if(i>=l)
			q.pop();
		cout<<q.get()<<' ';
	}

	return 0;
}