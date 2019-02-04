#include "Core.h"
#include "SplayTree.h"
#define endl '\n'//do not use when solving interactive problem!!!

u32 bino[11][11]={1,};

struct A{
	u32 arr[11]={0,};
	int cnt;

	static A zero(){ return {0,0}; }

	A(u32 n=0, int cnt=1):cnt(cnt){
		forh(i, 0, 11){
			arr[i]=n;
		}
	}

	A operator+(const A& r)const{
		int p[11]={1,};
		forh(i, 1, 11)
			p[i]=p[i-1]*cnt;
		
		A ret = *this;
		forh(i, 0, 11){
			forc(j, 0, i){
				ret.arr[i]+=p[j]*bino[i][j]*r.arr[i-j];
			}
		}
		ret.cnt+=r.cnt;

		return ret;
	}

	bool operator==(const A& r)const{return !memcmp(arr, r.arr, sizeof arr) && cnt==r.cnt;}
};

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(11);
	srand((u32)time(0));
	
	forh(i, 1, 11){
		bino[i][0]=1;
		forc(j, 1, i){
			bino[i][j]=bino[i-1][j-1]+bino[i-1][j];
		}
	}

	int n;
	cin>>n;
	SplayTree<A> st(n, [](const auto& a, const auto& b){return a+b;}, [](SplayTree<A>::Node* x){x->val=x->acc=x->lazy;}, [](const auto& a, const auto& b){return b;});
	forh(i,0,n){
		u32 x;
		cin>>x;
		st.update(i,x);
	}
	int m;
	cin>>m;
	forh(i, 0, m){
		int type;
		cin>>type;
		if(type==1){
			u32 p, v;
			cin>>p>>v;
			st.insert(p);
			st.update(p, v);
		}else if(type==2){
			u32 p;
			cin>>p;
			st.erase(p);
		}else if(type==3){
			u32 p,v;
			cin>>p>>v;
			st.update(p, v);
		}else{
			int l, r, k;
			cin>>l>>r>>k;
			cout<<st.query(l, r+1).arr[k]<<endl;
		}
	}

	return 0;
}
