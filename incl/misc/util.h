#pragma once 
#include "core/base.h"

template<class T>
auto split(auto s,T p) {
	Arr<decltype(s)> ret;
	auto it1=s.begin();
	for(auto it2=it1;(it2=find(it1,s.end(),p))!=s.end();it1=it2+1)
		ret.push_back({it1,it2});
	ret.push_back({it1,s.end()});
	return ret;
}

auto compress_eqcnt(const auto& a){
	using T=remove_reference<decltype(a.front())>::type;
	Arr<pair<T,int>> ret;
	if(a.empty())
		return ret;
	for(auto i:a)
		if(sz(ret) and ret.back().fi==i)
			ret.back().se++;
		else
			ret.emplace_back(move(i),1);
	return ret;
}

//NOTE: Arr<Op>는 재할당때문에 망한다. list<Op>::emplace_back만 쓰자.
//연산을 저장할땐 캡쳐변수 생명주기를 고려해야함.
//polygon, 르블랑의 트리순회, AC-downup-defer.cpp
struct Op{
	Op(function<void()> f):f(f){}
	~Op(){trigger();}
	void trigger(){f();f=[](){};}
	function<void()> f;
};