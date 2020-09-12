#pragma once
#include "RootedTree.h"

template<class T>
struct HLD: public RootedTree<T>{
	using RT=RootedTree<T>; using RT::n; using RT::r; using RT::p; using RT::ch; using RT::dpt;

	HLD(const Arr<pair<int,T>>& pi)
	:RT(pi), cn(n), top(n), v2pre(n){
		int cpre=0, ccn=0;
		dfs_hld(r, cpre, ccn);
		top[0]=0;
	}

	int lca(int a, int b){
		while(cn[a]!=cn[b]){
			if(dpt[top[cn[a]]]<dpt[top[cn[b]]]) b=p[top[cn[b]]].fi;
			else a=p[top[cn[a]]].fi;
		}
		return dpt[a]<dpt[b]?a:b;
	}
protected:
	Arr<int> cn,top,v2pre;//chain number, top of the chain, vertex to preorder

	void dfs_hld(int cur, int& cpre, int& ccn){
		if(sz(ch[cur]))
			swap(ch[cur].front(), *max_element(all(ch[cur]),[this](auto a, auto b){return this->tsz[a.fi]>this->tsz[b.fi];}));
		cn[cur]=ccn;
		rep(i,sz(ch[cur])){
			if(i)
				top[++ccn]=ch[cur][i].fi;
			dfs_hld(ch[cur][i].fi, cpre, ccn);
		}
	}
};
/*
	T q(int u, int v, bool edge_w=true){
		T ret = Q::id();
		int w = lca(u, v);
		while(cn[w]!=cn[u])
			ret = Q::f(ret, st.q(si[top[cn[u]]], si[u]+1)), u = p[top[cn[u]]].fi;
		ret = Q::f(ret, st.q(si[w]+edge_w, si[u]+1));
		
		while(cn[w]!=cn[v])
			ret = Q::f(ret, st.q(si[top[cn[v]]], si[v]+1)), v = p[top[cn[v]]].fi;
		ret = Q::f(ret, st.q(si[w]+edge_w, si[v]+1));

		return ret;
	}

	void upd(int cur, T w){return st.upd(si[cur], w);}
	void upd(int s, int e, T w){}*/
/*
#include <bits/stdc++.h>
using namespace std;
#define hfor(v, s, e) for(int v=(s);(s)<=v&&v<(e);++v)//half-opened range
#define hfori(v, s, e) for(int v=(e)-1;(s)<=v&&v<(e);--v)//inversion
#define rep(v,x) hfor(v,0,(x))
#define repi(v,x) hfori(v,0,(x))
#define all(x) (x).begin(),(x).end()
constexpr int lgc(int x){return 64-__builtin_clzll(x-1);}
using i64=long long;
#define int i64
int inf=987654321;

struct B{
	B(int n):n(n),tr(n*4),lz(n*4,inf){}
	int q(int s, int e){return q(1,0,n,s,e);}
	void upd(int s, int e, int v){upd(1,0,n,s,e,v);}

	int q(int c, int cs, int ce, int s, int e){
		prop(c,cs,ce);
		if(s<=cs and ce<=e) return tr[c];
		if(ce<=s or e<=cs) return 0;
		int m=(cs+ce)/2;
		return q(c*2,cs,m,s,e)+q(c*2+1,m,ce,s,e);
	}

	int upd(int c, int cs, int ce, int s, int e, int v){
		prop(c,cs,ce);
		if(s<=cs and ce<=e){
			lz[c]=v;
			prop(c,cs,ce);
			return tr[c];
		}
		if(ce<=s or e<=cs) return tr[c];
		int m=(cs+ce)/2;
		return tr[c]=upd(c*2,cs,m,s,e,v)+upd(c*2+1,m,ce,s,e,v);
	}
	void prop(int c, int cs, int ce){
		if(lz[c]!=inf){
			tr[c]=(ce-cs)*lz[c];
			if(ce-cs>1){
				lz[c*2]=lz[c];
				lz[c*2+1]=lz[c];
			}
			lz[c]=inf;
		}
	}

	int n;
	vector<int> tr,lz;
};

struct A{
	A(vector<vector<int>> g):n(g.size()),ch(n),p(n,vector<int>(lgc(n),-1)),s(n),d(n),v2pr(n),top(n),seg(n){
		init(0,0,0,g);
		pre(0);
	}
	int init(int v, int pa, int dpt, const vector<vector<int>>&g){
		s[v]=1, d[v]=dpt, p[v][0]=pa;
		for(auto i:g[v])
			if(i!=pa){
				s[v]+=init(i,v,dpt+1,g);
				ch[v].push_back(i);
				if(s[ch[v].front()]<s[i])
					swap(ch[v].front(),ch[v].back());
			}
		return s[v];
	}
	void pre(int v){
		v2pr[v]=pr.size(),pr.push_back(v);
		for(auto i:ch[v])
			top[i]=(i==ch[v].front()?top[v]:i), pre(i);
	}
	int panc(int x, int k){
		if(p[x][k]!=-1)return p[x][k];
		return p[x][k]=panc(panc(x,k-1),k-1);
	}
	int lca(int u, int v){
		if(d[u]>d[v])swap(u,v);
		repi(i,lgc(n))
			if(d[panc(v,i)]>=d[u])
				v=panc(v,i);
		if(u==v)return u;
		repi(i,lgc(n))
			if(panc(u,i)!=panc(v,i))
				u=panc(u,i), v=panc(v,i);
		return panc(u,0);
	}
	void upd(int u, int v, int x){
		int z=lca(u,v);

		for(;u and v2pr[top[u]]>=v2pr[z];u=panc(top[u],0))
			seg.upd(v2pr[top[u]],v2pr[u]+1,x);
		seg.upd(v2pr[z],v2pr[u]+1,x);

		for(;v and v2pr[top[v]]>=v2pr[z];v=panc(top[v],0))
			seg.upd(v2pr[top[v]],v2pr[v]+1,x);
		seg.upd(v2pr[z],v2pr[v]+1,x);
	}
	int q(int x){return seg.q(v2pr[x],v2pr[x]+s[x]);}
	int np(int x){
		if(q(x)) return x;
		repi(i,lgc(n))
			if(!q(panc(x,i)))
				x=panc(x,i);
		return panc(x,0);
	}
	int npd(int x){return d[x]-d[np(x)];}

	int n;
	vector<vector<int>> ch, p;
	vector<int> s, d, pr, v2pr, top;
	B seg;
};

signed main(){
    cin.sync_with_stdio(0),cin.tie(0);
	int n; cin>>n;
	vector<vector<int>> g(n);
	rep(i,n-1){
		int u,v; cin>>u>>v;
		u--,v--;
		g[u].push_back(v), g[v].push_back(u);
	}
	A hld(g);
	int q; cin>>q;
	int ans=0;
	while(q--){
		int k,u,v; cin>>k>>u>>v; u--,v--;
		int z=hld.lca(u,v);
		if(k==1){
			ans+=hld.npd(u);
			ans+=hld.npd(v);
			ans-=hld.npd(z);

			hld.upd(u,v,1);
		}else{
			if(hld.q(z)){
				u=hld.np(u), v=hld.np(v);
				hld.upd(u,v,0);

				ans-=hld.npd(u);
				ans-=hld.npd(v);
				ans+=hld.npd(z);
			}
		}
		cout<<ans*2<<endl;
	}
}
 */
