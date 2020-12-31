#pragma once
#include "Core.h"

struct Node{
    signed cs,ce,v,w;
    Node *l,*r;

    void upd(signed s, signed e, char x){
        if(ce<=s or e<=cs)return;
        if(s<=cs and ce<=e){
            w+=x;
            v=w?ce-cs:(l?l->v:0)+(r?r->v:0);
            return;
        }
        signed m=(cs+ce)/2;
        if(!l)l=new Node{cs,m};
        if(!r)r=new Node{m,ce};
        l->upd(s,e,x), r->upd(s,e,x);
        v=w?ce-cs:l->v+r->v;
    }
} root{0,signed(1e9+9)};

int solution(vector<vector<signed> > rects)
{
    map<signed,Arr<tint>> a;
    for(auto& i:rects){
        a[i[0]].emplb(i[1],i[3],1);
        a[i[2]].emplb(i[1],i[3],-1);
    }

    int ans=0;
        signed px=0;
        signed pv=0;
    for(auto [x,ev]:a){
        for(auto [y1,y2,d]:ev)
            root.upd(y1,y2,d);
        ans+=pv*int(x-px);
        px=x, pv=root.v;
    }
    return ans;
}

struct A{
	static A *id;
	int x=0; A *l=id,*r=id;
	void upd(int i, int v){upd(0,1e9,i,v);}
	int q(int s, int e){return q(0,1e9,s,e);}
private:
	int upd(int cs, int ce, int i, int v){
		int cm=(cs+ce)>>1;
		if(i<=cs and ce<=i+1)return x+=v;
		if(ce<=i or i+1<=cs)return x;
		if(l==id)l=new A{};
		if(r==id)r=new A{};
		return x=l->upd(cs,cm,i,v)+r->upd(cm,ce,i,v);
	}
	int q(int cs, int ce, int s, int e){
		int cm=(cs+ce)>>1;
		if(s<=cs and ce<=e)return x;
		if(ce<=s or e<=cs)return A::id->x;
		return l->q(cs,cm,s,e)+r->q(cm,ce,s,e);
	}
};
A* A::id=new A{};
auto id=A::id->l=A::id->r=A::id;
