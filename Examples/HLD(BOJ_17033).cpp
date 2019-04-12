#include "Core.h"
#include "HLD.h"
//Do not use it when solving interactive problems!!!
#define endl '\n'

struct F{
  static int idT(){return 0;}
  static int q(const int& a, const int& b){return a^b;}
  static int upd(const int& a, const int& b){return b;}
};

int main(){
  ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  cout<<fixed<<setprecision(11);
  srand((u32)time(0));

  int n,q;
  cin>>n>>q;
  int c[100000];
  Tree<int> t(n);
  forh(i,0,n)
    cin>>c[i];
  forh(i,0,n-1){
    int a,b;
    cin>>a>>b;
    t.add_edge(--a,--b, 1);
  }
  HLD<int,int,F> hld(t, 0);
  forh(i,0,n)
    hld.update(i, c[i]);
  forh(i,0,q){
    int a,b,c;
    cin>>a>>b>>c;
    if(a==1){
      hld.update(--b, c);
    }else{
      cout<<hld.query(--b, --c, false)<<endl;
    }
  }

  return 0;
}