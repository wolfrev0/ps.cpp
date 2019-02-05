#pragma once
#include "LCA.h"

template<typename T>
struct HLD:public LCA<T>{
  using LCA<T>::n;
  using LCA<T>::r;
  using LCA<T>::parent;
  using LCA<T>::children;
  using LCA<T>::lca;

  HLD(const Tree<T>& t, int r, const function<T(T, T)>& qf, const function<T(T,T)>& uf)
  :LCA<T>(t, r), qf(qf), uf(uf), st(n, qf, uf), chain(n), head(n), segidx(n), sz(n){
    dfs_size(r);
    int segi=0, cur_chain=0;
    dfs_hld(r, segi, cur_chain);
    head[0]=0;
  }

  T query(int u, int v, bool edge_w=true){
    T ret = T::zero();
    int w = lca(u, v);
    while(chain[w]!=chain[u])
      ret = qf(ret, st.query(segidx[head[chain[u]]], segidx[u]+1)), u = parent[head[chain[u]]].e;
    ret = qf(ret, st.query(segidx[w]+edge_w, segidx[u]+1));

    while(chain[w]!=chain[v])
      ret = qf(ret, st.query(segidx[head[chain[v]]], segidx[v]+1)), v = parent[head[chain[v]]].e;
    ret = qf(ret, st.query(segidx[w]+1, segidx[v]+1));

    return ret;
  }

  void update(int s, int e, T w){
    
  }

  void update(int cur, T w){
    st.update(segidx[cur], w);
  }
protected:
  const function<T(T, T)> qf, uf;
  SegmentTree<T> st;
  vector<int> chain;
  vector<int> head;
  vector<int> segidx;
  vector<int> sz;

  int dfs_size(int cur){
    sz[cur]=1;
    for(const auto& i:children[cur])
      sz[cur]+=dfs_size(i.e);
    sort(children[cur].begin(), children[cur].end(), [&](auto a, auto b){return sz[a.e]>sz[b.e];});
    return sz[cur];
  }

  void dfs_hld(int cur, int& segi, int& cur_chain){
    st.update(segidx[cur]=segi++, parent[cur].w);
    chain[cur]=cur_chain;
    auto c = children[cur];
    forh(i, 0, c.size()){
      if(i)
        head[++cur_chain]=c[i].e;
      dfs_hld(c[i].e, segi, cur_chain);
    }
  }
};