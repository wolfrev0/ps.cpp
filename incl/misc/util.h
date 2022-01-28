#pragma once 
#include "core/base.h"

auto split(auto s,auto p) {
	Arr<decltype(s)> ret;
	auto it1=s.begin();
	for(auto it2=it1;(it2=find(it1,s.end(),p))!=s.end();it1=it2+1)
		ret.pushb({it1,it2});
	ret.pushb({it1,s.end()});
	return ret;
}

struct defer{defer(auto f):f(f){}~defer(){f();}function<void()> f;};
#define defer(x) auto _##__COUNTER__=defer([&](){x;});