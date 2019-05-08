#include "Core.h"
#define endl '\n'//do not use when solving interactive problem!!!

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(11);
	srand((unsigned)time(0));

	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int a=-1, b=-1;
		trav(i,2,i*i<=2*n){
			if(2*n%i)
				continue;
			int x=2*n/i;
			int y=i;
			if((x-y+1)%2 || (x+y-1)%2)
				continue;
			a=(x-y+1)/2;
			b=(x+y-1)/2;
			break;
		}
		if(a<0)
			cout<<"IMPOSSIBLE"<<endl;
		else{
			cout<<n<<" = ";
			forh(i,a,b)
				cout<<i<<" + ";
			cout<<b<<endl;
		}
	}
	
	return 0;
}
