#include "Core.h"
#include "SegPers.h"
#include "XArr.h"
#define endl '\n'//not interactive?
#define int i64//overflow?

signed main(){
	int n;
	cin>>n;
	vector<int> arr(n);
	hfor(i,0,n)
		cin>>arr[i];
	int m;
	cin>>m;
		
	SegPersSum<int> pst(n);
	using Node=SegPers<int>::Node;
	XArr<Node*> vers(m);
	pst.build(vers[-1]=new Node(), arr);

	int vi=0;
	hfor(i,0,m){
		int op;
		cin>>op;
		if(op==1){
			int i, v;
			cin>>i>>v;
			i--;
			vers[vi]=pst.upd(vers[vi-1], i, v);
			vi++;
		}else{
			int k, i, j;
			cin>>k>>i>>j;
			k--,i--,j--;
			cout<<pst.q(vers[k], i, j+1)<<endl;
		}
	}

	return 0;
}