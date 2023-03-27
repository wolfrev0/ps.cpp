#pragma once
#include "core/base.h"

pint bisect(auto det,int s=-inf<int>(),int e=inf<int>()){
	bool ds=det(s),de=det(e);
	if(ds==de)
		return {ds,de};
	while(e-s>1){
		int m=(s+e)/2;
		if(det(m)==ds) s=m;
		else e=m;
	}
	return {s,e};
};
template<auto cmp>
tint ternary(auto val,int s=-inf<int>(),int e=inf<int>()){
	auto [rs,re]=bisect(lam(cmp(val(mid),val(mid+1)),int mid),s,e-1);
	return {rs,re,re+1};
};
