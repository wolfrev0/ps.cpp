#pragma once
#include "WeightedGraph.h"

struct Graph: public WeightedGraph<int>{
	Graph(int n):WeightedGraph<int>(n) {}

	inline void add_edge(int s, int e, bool dir=true) {
		WeightedGraph::add_edge(s, e, 1, dir);
	}

	vector<int> topo_sort() {
		vector<int> in(n);
		forh(i, 0, n){
			for(auto &j:g[i])
				in[j.e]++;
		}
		queue<int> q;
		forh(i, 0, n)
			if (!in[i])
				q.push(i);
		vector<int> ret;
		while (q.size()) {
			auto cur = q.front();
			ret.push_back(cur);
			q.pop();
			for (auto &i : g[cur])
				if (--in[i.e] == 0)
					q.push(i.e);
		}
		reverse(ret.begin(), ret.end());
		return ret;
	}

	pair<vector<vector<int>>, Graph> scc(){
		vector<int> state(n), ord(n), scc_id(n, -1);
		stack<int> stk;
		int o=0, scc_cnt=0;
		forh(i, 0, n){
			if(!state[i])
				dfs_scc(i, o, scc_cnt, state, ord, scc_id, stk);
		}

		auto group=vector<vector<int>>(scc_cnt);
		forh(i, 0, n)
			group[scc_id[i]].push_back(i);
		Graph sccg(scc_cnt);
		forh(i, 0, n){
			for(auto& j:g[i])
				if(scc_id[i]!=scc_id[j.e])
					sccg.add_edge(scc_id[i], scc_id[j.e]);
		}

		return {group, sccg};
	}

private:
	int dfs_scc(int v, int& o, int &scc_cnt, vector<int>& state, vector<int>& ord, vector<int>& scc_id, stack<int>& stk){
		state[v]=1;
		stk.push(v);
		int ret = ord[v]=o++;
		for(auto i: g[v]){
			switch(state[i.e]){
				case 0:
					ret = min(ret, dfs_scc(i.e, o, scc_cnt, state, ord, scc_id, stk));
					break;
				case 1://back
					ret = min(ret, ord[i.e]);
					break;
				case 2:
					if(ord[i.e]>ord[v])//fwd
						;
					else if(ord[i.e]<ord[v]){//cross
						if(scc_id[i.e]==-1)
							ret = min(ret, ord[i.e]);
					}
					else//loop
						;
					break;
			}
		}
		if(ret == ord[v]){
			int cur;
			do{
				cur = stk.top();
				stk.pop();
				scc_id[cur]=scc_cnt;
			}while(stk.size() && cur!=v);
			scc_cnt++;
		}

		state[v]=2;
		return ret;
	}
};

struct UndirectedGraph: public Graph{
	UndirectedGraph(int n):Graph(n){}

	inline void add_edge(int s, int e) {
		Graph::add_edge(s, e, false);
	}

	vector<int> articul_points(){
		vector<int> ord(n, -1), ret;
		int o=0;
		forh(i, 0, n){
			if(ord[i] != -1)
				continue;
			dfs_ap(i, -1, o, ord, ret);
		}
		return ret;
	}

	vector<pair<int,int>> bridges(){
		vector<int> ord(n, -1);
		vector<pair<int,int>> ret;
		int o=0;
		forh(i, 0, n){
			if(ord[i] != -1)
				continue;
			dfs_bridge(i, -1, o, ord, ret);
		}
		return ret;
	}

	void bcc(){

	}
private:
	int dfs_ap(int v, int p, int& o, vector<int>& ord, vector<int>& ans){
		int ret = ord[v]=o++;
		int subcnt=0;
		bool isAP = false;
		for(auto i: g[v]){
			if(ord[i.e] != -1){
				ret = min(ret, ord[i.e]);
				continue;
			}

			int res=dfs_ap(i.e, v, o, ord, ans);
			subcnt++;
			isAP |= res>=ord[v];
			ret = min(ret, res);
		}
		if(isAP && (p!=-1 || subcnt>1))
				ans.push_back(v);
		return ret;
	}
	int dfs_bridge(int v, int p, int& o, vector<int>& ord, vector<pair<int, int>>& ans){
		int ret = ord[v]=o++;
		bool conn = false;
		for(auto i: g[v]){
			if(ord[i.e] != -1){
				if(p!=-1)
					conn |= ord[i.e]<ord[p];
				ret = min(ret, ord[i.e]);
				continue;
			}

			int res=dfs_bridge(i.e, v, o, ord, ans);
			conn |= res<ord[v];
			ret = min(ret, res);
		}
		if(!conn && p!=-1)
				ans.push_back({min(v, p), max(v, p)});
		return ret;
	}
};