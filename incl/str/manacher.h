#pragma once
#include "core/base.h"

template<class T> pair<Arr<int>,Arr<int>> manacher(Str<T> a){
	int n=sz(a);
	Arr<int> od(n),ed(n);
	//od[i]==k ->i중심으로 길이k 팰린드롬 존재
	//ed[i]==k ->i-1,i중심으로 길이k 팰린드롬 존재(od에 큰 변경없게하기 위해 중심을 i-1,i로 잡음)
	for(int i=0,s=0,e=0;i<n;i++){
		int k=i>=e?1:min(od[s+(e-i)-1],e-i);
		while(0<=i-k&&i+k<n and a[i-k]==a[i+k])k++;
		od[i]=k;
		if(i+k>e)s=i-k+1,e=i+k;
	}
	for(int i=0,s=0,e=0;i<n;i++){
		int k=i>=e?0:min(ed[s+(e-i)],e-i);
		while(0<=i-k-1&&i+k<n and a[i-k-1]==a[i+k])k++;
		ed[i]=k;
		if(i+k>e)s=i-k,e=i+k;
	}
	return {od,ed};
}