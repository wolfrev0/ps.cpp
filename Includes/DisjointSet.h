#pragma once
#include "Core.h"

struct DisjointSet {
  vector<int> par;
  vector<int> sz;

  DisjointSet(int n): par(n),sz(n,1){
    forh(i,0,n)
      par[i]=i;
  }

  void uni(int a, int b){
    a=find(a), b=find(b);
    if(a==b)
      return;
    par[b]=a;
    sz[a]+=sz[b];
  }

  int find(int a){
    if(par[a]==a)
      return a;
    return par[a]=find(par[a]);
  }

  int size(int a){return sz[find(a)];}
};