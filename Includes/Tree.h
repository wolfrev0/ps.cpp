#pragma once
#include "Graph.h"

template<typename T>
struct Tree: public Graph<T>{
  Tree(int n=0):Graph<T>(n){}
  Tree(const Tree& r):Graph<T>(r){}
  using Graph<T>::n;
  using Graph<T>::g;

  void add_edge(int s, int e, T w){
    Graph<T>::add_edge(s, e, w, false);
  }

  T diameter()const {
    return dfs_diameter(0, -1).first;
  }
private:
  pair<T, T> dfs_diameter(int v, int p)const{
    T diam = 0;
    vector<int> lens;
    for(auto i:g[v]){
      if(i.e==p)
        continue;
      auto res=dfs_diameter(i.e, v);
      diam=max(diam, res.first);
      lens.push_back(res.second + i.w);
    }
    int len=0;
    if(lens.size()==1){
      diam=max(diam, len=lens.back());
    }
    else if(lens.size()>1){
      auto it = max_element(lens.begin(), lens.end());
      len=*it; lens.erase(it);
      it=max_element(lens.begin(), lens.end());
      diam=max(diam, len+*it);
    }
    return {diam,len};
  }
};