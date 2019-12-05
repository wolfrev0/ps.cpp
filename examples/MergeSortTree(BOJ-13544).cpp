#include "Core.h"
#include "MergeSortTree.h"
#define endl '\n'//do not use when solving interactive problem!!!

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(11);
	srand((unsigned)time(0));

	int n;
	cin>>n;
	int arr[100000];
	forh(i, 0, n){
		cin>>arr[i];
	}
	MergeSortTree t({arr, arr+n});
	int m;
	cin>>m;
	int la=0;
	forh(i, 0, m){
		int a, b, c;
		cin>>a>>b>>c;
		int d=a^la;
		int e=b^la;
		int f=c^la;
		d--, e--;
 		cout<<(la=t.query(d,e+1,f))<<endl;
	}

	return 0;
}