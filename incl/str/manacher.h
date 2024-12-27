#pragma once
#include "core.h"

//only finds odd palindromes
//to find even palindromes, convert string "abcd" to "#a#b#c#d#"
//https://www.acmicpc.net/submit/11046/48519822
//#변형시, manacher[i]은 변형전의 팰린드롬 길이가 된다.
template<class T> Arr<int> manacher(Str<T> a){
	int n=sz(a);
	Arr<int> b(n+1);
	int c=-1;
	//b[i] = a[i-b[i],i+b[i]] is palindrome
	//c: rightest palindrome index
	//let j = c-(i-c) = flipped index of i based on c
	//generally, a[c-b[c],j] is inversion of a[i,c+b[c]]
	//but we takes only as much b[c-(i-c)] which is palindrome, so that two is identical
	for(int i=0;i<n;i++){
		b[i] = i>c+b[c] ? 0 : min(c+b[c]-i,b[c-(i-c)]);
		while(i+b[i]+1<n and i-b[i]-1>=0 and a[i+b[i]+1]==a[i-b[i]-1])
			b[i]++;
		if(c+b[c]<i+b[i])
			c=i;
	}
	return b;
}

template<class T> pair<Arr<int>,Arr<int>> manacher_legacy(Str<T> a){
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
