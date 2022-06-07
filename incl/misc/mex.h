#pragma once
#include "core/base.h"
#include "misc/gccext.h"

//TODO: DynSeg+BinaryLifting해서 복잡도 log로 개선하기
struct Mex{
	pbds_map<int,int> a;
	void add(int x){a[x]++;}
	void del(int x){
		auto it=a.find(x);
		MUST(it!=a.end());
		if(!--(it->se))
			a.erase(it);
	}
	int mex(){
		int s=-1,e=sz(a);
		while(e-s>1){
			int m=(s+e)/2;
			if((int)a.order_of_key(m+1)==m+1)s=m;//m까지 다 있음
			else e=m;//m까지 빠진게 있음
		}
		return e;
	}
};