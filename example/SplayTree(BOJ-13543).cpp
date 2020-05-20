#include "Core.h"
#include "SplayTree.h"
#define endl '\n'//do not use when solving interactive problem!!!

unsigned bino[11][11]={1,};

struct A{
	unsigned arr[11]={0,};
	int cnt;

	A(unsigned n=0, int cnt=0):cnt(cnt){
		hfor(i, 0, 11){
			arr[i]=n;
		}
	}

	A operator+(const A& r)const{
		int p[11]={1,};
		hfor(i, 1, 11)
			p[i]=p[i-1]*cnt;
		
		A ret = *this;
		hfor(i, 0, 11){
			forc(j, 0, i){
				ret.arr[i]+=p[j]*bino[i][j]*r.arr[i-j];
			}
		}
		ret.cnt+=r.cnt;

		return ret;
	}

	bool operator==(const A& r)const{return !memcmp(arr, r.arr, sizeof arr) && cnt==r.cnt;}
};

using Node = SplayNode<A, A>;

struct F{
	static A q(const auto& a, const auto& b){return a+b;}
	static void upd(Node* x){x->val=x->acc=x->lazy;}
	static A propa(const auto& a, const auto& b){return b;}
};

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(11);
	srand((unsigned)time(0));
	
	hfor(i, 1, 11){
		bino[i][0]=1;
		forc(j, 1, i){
			bino[i][j]=bino[i-1][j-1]+bino[i-1][j];
		}
	}

	int n;
	cin>>n;
	SplayTree<A,A,F> st;
	hfor(i,0,n){
		unsigned x;
		cin>>x;
		st.insert(i,{x, 1});
	}
	int m;
	cin>>m;
	hfor(i, 0, m){
		int type;
		cin>>type;
		if(type==1){
			unsigned p, v;
			cin>>p>>v;
			st.insert(p, {v, 1});
		}else if(type==2){
			unsigned p;
			cin>>p;
			st.erase(p);
		}else if(type==3){
			unsigned p,v;
			cin>>p>>v;
			st.update(p, {v, 1});
		}else{
			int l, r, k;
			cin>>l>>r>>k;
			cout<<st.query(l, r+1).arr[k]<<endl;
		}
	}

	return 0;
}
