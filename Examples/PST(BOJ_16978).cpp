#include "Core.h"
#include "PST.h"
#include "XArr.h"
#define endl '\n'//do not use when solving interactive problem!!!

int main(){
  ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  cout<<fixed<<setprecision(11);
  srand((u32)time(0));

  int n;
  cin>>n;
  int arr[100000];
  forh(i,0,n)
    cin>>arr[i];
  int m;
  cin>>m;
    
  PST<i64> pst(n, [](i64 a, i64 b){return a+b;});
  XArr<PST<i64>::Node*> vers(m);
  pst.build(vers[-1]);
  forh(i,0,n)
    pst.upgrade(vers[0], vers[-1], i, arr[i]), vers[-1]=vers[0];

  int vi=0;
  forh(i,0,m){
    int op;
    cin>>op;
    if(op==1){
      int i, v;
      cin>>i>>v;
      i--;
      pst.upgrade(vers[vi], vers[vi-1], i, v);
      vi++;
    }else{
      int k, i, j;
      cin>>k>>i>>j;
      k--,i--,j--;
      cout<<pst.query(vers[k], i, j+1)<<endl;
    }
  }


  return 0;
}