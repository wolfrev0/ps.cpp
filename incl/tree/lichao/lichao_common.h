#pragma once
#include "geom/line.h"

//Between for any of two different function, the number of intersection is no more than 1.
//T: callable data type, Line<long double> recommended
//T id(): identity element of T
//bool cmp(T l, T r, fp x): Node will choose larger one by comparing l(x) and r(x).
//max lichao: id=Line(0,-inf), cmp(l,r,x)=l(x)<r(x)
//min lichao: id=Line(0,inf), cmp(l,r,x)=r(x)<l(x)

// NOTE: Integer lichao is bad idea. It requires i128 in most cases and perform bad.
// 반평면땅따먹기(12795)는 i128로 풀수도 없음. 아래는 나무자르기(13263)결과
// i128(664ms): https://www.acmicpc.net/source/64946225
// long double(212ms): https://www.acmicpc.net/source/64946268
template<typename T> concept LiChaoType=requires(T t){
	t(1);
};