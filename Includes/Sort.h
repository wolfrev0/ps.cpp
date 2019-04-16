#pragma once
#include "Core.h"

template<typename T>
void counting_sort(vector<T>& v, const function<T(T)> &f = [](const T& x){return x;})
{
	const int MAX_BW = 500001;
	static vector<T> bucket[MAX_BW+1];
	for(auto &i:bucket)
		i.clear();

		T m = T::inf(), M = -T::inf();
		for(auto &i:v){
				m = min(m, f(i));
				M = max(M, f(i));
		}

		for(auto i:v)
				bucket[f(i) - m].push_back(i);
		v.clear();
		forc(i, 0, M-m)
				for(auto j:bucket[i])
						v.push_back(j);
}