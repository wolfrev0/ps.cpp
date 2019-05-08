#include "Core.h"
#include "Seg.h"
#include "Matrix.h"
//Do not use it when solving interactive problems!!!
#define endl '\n'
//#define int i64
//using PII=Pair<int,int>;

const int dirs[4][2]={{0,1},{0,-1},{1,0},{-1,0}};

struct T{Mat<int, 3> a=1;};

using U=Mat<int,3>;
struct F{
  static T q(const T& a, const T& b){return {a.a*b.a};}
  static T upd(const T& a, const U& b){return {b};}
};

signed main(){
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout<<fixed<<setprecision(11);
	srand((int)time(0));

  int n,q,w;
  int a[250000];
  cin>>n>>q>>w;
  forh(i,0,n)
    cin>>a[i];
  array<int,3> v={0,0,1};

  Seg<T, Mat<int,3>, F> st(n);
  st.update(n-1-0, Mat<int, 3>({{{0,1,0},{0,1,1},{0,0,1}}}));
  forh(i,1,n)
    st.update(n-1-i, Mat<int, 3>({{{0,1,0},{a[i]+a[i-1]<=w,!(a[i]+a[i-1]<=w),1},{0,0,1}}}));
  int ans=(st.query(0, n).a*v)[1];
  if(a[0]+a[n-1]<=w)
    ans=min(ans, (st.query(1, n-1).a*v)[1]+1);
  cout<<ans<<endl;

  forh(i,0,q){
    int x,y;
    cin>>x>>y;
    x--;
    a[x]=y;
    if(x)
      st.update(n-1-x, Mat<int, 3>({{{0,1,0},{a[x]+a[x-1]<=w,!(a[x]+a[x-1]<=w),1},{0,0,1}}}));
    if(x+1<n)
      st.update(n-1-x-1, Mat<int, 3>({{{0,1,0},{a[x]+a[x+1]<=w,!(a[x]+a[x+1]<=w),1},{0,0,1}}}));
    int ans=(st.query(0, n).a*v)[1];
    if(a[0]+a[n-1]<=w)
      ans=min(ans, (st.query(1, n-1).a*v)[1]+1);
    cout<<ans<<endl;
  }

  return 0;
}