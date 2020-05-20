#include "Core.h"
#include "CumulQ.h"
#define endl '\n'//not interactive?
//#define int i64//overflow?

int n, m;
char a[2][500][500];

bool f(const vector<i64>& a, const vector<i64>& b){
	int ai=0, bi=0;
	while(ai<a.size() && bi<b.size()){
		while(ai<a.size() && a[ai]<b[bi])
			ai++;
		while(bi<b.size() && b[bi]<a[ai])
			bi++;
		if(ai<a.size() && bi<b.size() && a[ai]==b[bi])
			return true;
	}
	return false;
}

bool det(int x){
	vector<HashPairQ<mod, 1073741783>> v[2];
	hfor(k,0,2){
		v[k].resize(n);
		hfor(i,0,n)
			hfor(j,0,x)
				v[k][i].push(a[k][i][j]);
	}
	hfor(j,x,m){
		vector<i64> w[2];
		hfor(k,0,2)
			hfor(i,0,n)
				w[k].push_back(v[k][i].get());
		sort(all(w[0])), sort(all(w[1]));
		if(!f(w[0], w[1]))
			return true;
		hfor(k,0,2)
			hfor(i,0,n){
				v[k][i].push(a[k][i][j]);
				v[k][i].pop();
			}
	}
	vector<i64> w[2];
	hfor(k,0,2)
		hfor(i,0,n)
			w[k].push_back(v[k][i].get());
	sort(all(w[0])), sort(all(w[1]));
	return !f(w[0], w[1]);
}

signed main(){
	cin>>n>>m;
	hfor(k,0,2)
		hfor(i,0,n)
			hfor(j,0,m)
				cin>>a[k][i][j];
	int s=0, e=m;
	while(e-s>1)
		(det((e+s)/2)?e:s)=(e+s)/2;
	cout<<e<<endl;

	return 0;
}
