#pragma once
#include "core/base.h"

//Monge인거
//합,최대,최소
//최대-최소
//distinct count
//거리(r-l+1)
//최대연속부분합

// template<int lim=100>
//NOTE: Monge정의에 따르면 k=0부터 시작할 수 있는데 퇴화구간?경계값?이라 그런가 잘 안되고 k=max(i,j)+1부터 해야 잘 테스트됨. 단순합만 구해도 FAIL인걸 보면 퇴화구간에 대한 값이 정의되지 않아서 그런듯하다.
/*void solve(){
	int n=33;
	Arr<int> a(n); for(auto&i:a)i=rd(-9,10);
	shuffle(a.begin(),a.end(),_rng);
	func(int,f,int s,int e){
		MUST(s<e);
		return reduce(a.begin()+s,a.begin()+e);
	};
	println(test_monge(n,n,f));
}*/
bool test_monge(int n,int m,auto f){
	for(int i=0;i<n;i++)
		for(int j=i+1;j<n;j++)
			for(int k=j+1;k<m;k++)
				for(int l=k+1;l<m;l++){
					if(f(i,l)+f(j,k)<=f(i,k)+f(j,l)){
						// println("OK");
					}else{
						// dbg(i,j,k,l,f(i,l),f(j,k),f(i,k),f(j,l));
						return false;
					}
				}
	return true;
}
//min_opt_idx right monotonicity check
//max는 f에서 부호뒤집어 반환
//L은 함수 따로 만들자
//j>=i 제약 없을때도 있는데 일단 넣음
bool test_monoptiR(int n,int m,auto f){
	int popti=-1;
	for(int i=0;i<n;i++){
		pint val={inf<int>(),-1};
		for(int j=i;j<=m;j++)
			assmin(val,pint{f(i,j),j});
		if(val.se < popti)
			return false;
		// println("OK");
		popti=val.se;
	}
	return true;
}