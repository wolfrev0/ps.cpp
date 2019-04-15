#pragma once
#include "Core.h"

template<typename T, int n>
struct Mat{
  int a[n][n];
  Mat(){
    forh(i,0,n)
      forh(j,0,n)
        a[i][j]=i==j;
  }
  Mat(const int arr[][n]){memcpy(a, arr, sizeof a);}

  Mat operator*(const Mat& r)const{
    int ret[n][n]={0,};
    forh(i,0,n)
      forh(j,0,n)
        forh(k,0,n)
          ret[i][j]+=a[i][k]*r.a[k][j];
    return ret;
  }
  vector<int> operator*(const vector<int>& r)const{
    vector<int> ret(n);
    forh(i,0,n)
      forh(j,0,n)
        ret[i]+=a[i][j]*r[j];
    return ret;
  }

  void transpose(){}
  void gauss_elim(){}
};