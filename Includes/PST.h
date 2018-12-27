#pragma once
#include "Core.h"

template<typename T>
struct PST{
	struct Node{
		T val;
		Node *l, *r;

		Node(T v=0, Node* l=nullptr, Node* r=nullptr):val(v), l(l), r(r){}
	};

	const int n;
	const function<T(T,T)> f;
	vector<Node> vers;
	Node *base=new PST<ll>::Node(0);

	PST(int n, const function<T(T,T)>& f=[](T a, T b){return a+b;}):n(n), f(f), vers(n){
		build_base(base, 0, n-1);
	}
	
	Node* ver(int i) { return i>=0?&vers[i]:base; }
	
	void upgrade(Node* prev, Node* cur, int idx, T value){
		upgrade2(prev, cur, idx, value, 0, n-1);
	}

	T query(Node* node, int l, int r){
		return query2(node, l, r, 0, n-1);
	}

private:
	void build_base(Node* node, int low, int high)
	{
		if (low == high)
		{
			node->val = 0;
			return;
		}
		int mid = (low + high) / 2;
		node->l = new Node(0);
		node->r = new Node(0);
		build_base(node->l, low, mid);
		build_base(node->r, mid + 1, high);
		node->val = f(node->l->val, node->r->val);
	}
	void upgrade2(Node* prev, Node* cur, int idx, T value, int low, int high)
	{
		if (idx > high or idx < low or low > high)
			return;

		if (low == high)
		{
			cur->val = value;
			return;
		}
		int mid = (low + high) / 2;
		if (idx <= mid)
		{
			cur->r = prev->r;
			cur->l = new Node(0);
			upgrade2(prev->l, cur->l, idx, value, low, mid);
		}
		else
		{
			cur->l = prev->l;
			cur->r = new Node(0);
			upgrade2(prev->r, cur->r, idx, value, mid + 1, high);
		}
		cur->val = f(cur->l->val, cur->r->val);
	}

	T query2(Node* node, int l, int r, int low, int high)
	{
		if (l > high or r < low or low > high)
			return 0;
		if (l <= low and high <= r)
			return node->val;
		int mid = (low + high) / 2;
		return f(query2(node->l, l, r, low, mid), query2(node->r, l, r, mid + 1, high));
	}
};