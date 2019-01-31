#include "Core.h"
#include "NumberTheory.h"
#include "ModNum.h"
#include "SegmentTree.h"
#define endl '\n'//do not use when solving interactive problem!!!

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(11);
	srand((u32)time(0));
	
	int n, m, k;
	cin>>n>>m>>k;
	SegmentTreeLazy<i64> st(n, 1, I32::inf(), [](auto a, auto b){return a*b%mod;}, [](auto a, auto b, int cnt){return /*fastpow<ModNum>(b, cnt).val()%mod*/b;}, [](auto a, auto b){return b;});
	forh(i,0,n){
		i64 x;
		cin>>x;
		st.update(i,x);
	}
	forh(i, 0, m+k){
		int a;
		cin>>a;
		if(a==1){
			int b;
			i64 c;
			cin>>b>>c;
			b--;
			st.update(b, b+1, c);
		}else{
			int b, c;
			cin>>b>>c;
			b--, c--;
			cout<<st.query(b, c+1)<<endl;
		}
	}

	return 0;
}
