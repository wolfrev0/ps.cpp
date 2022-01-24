#include "core/base.h"
#include "misc/random.h"

//Monge인거
//합,최대,최소
//최대-최소
//distinct count
//거리(r-l+1)
//

#include "math/frac.h"
void solve(){
	int n=100;
	Arr<int> a(n); for(auto&i:a)i=rd(-9,10);
	shuffle(a.begin(),a.end(),_rng);
	func(Frac,f,int s,int e){
		int ret=0;
		int sumacc=0;
		int minacc=inf<int>();
		for(int i=s;i<e;i++){
			sumacc+=a[i];
			ret=max(ret,sumacc-minacc);
			minacc=min(minacc,sumacc);
		}
		return ret;

		int lo=inf<int>(),hi=-inf<int>(),sum=0;
		for(int i=s;i<e;i++)
			lo=min(lo,a[i]),hi=max(hi,a[i]),sum+=a[i];
		int ds=0;
		for(int i=s;i<e-1;i++)
			ds+=abs(a[i+1]-a[i]);
		// return ds+hi+(e-s);
		// return abs(hi-(e-s));
		Arr<int> b(a.begin()+s,a.begin()+e);
		sort(b.begin(),b.end());
		return sum;
	};
	for(int i=0;i<n;i++)
		for(int j=i+1;j<n;j++)
			for(int k=j+1;k<n;k++)
				for(int l=k+1;l<n;l++)
					cout<<(f(i,l)+f(j,k)<=f(i,k)+f(j,l));
					// assert(f(i,l)+f(j,k)<=f(i,k)+f(j,l));
}
signed main(){
	// int ti=0,t;cin>>t;
	// while(++ti<=t)
	// 	cout<<"Case #"<<ti<<": ",
		solve();
}