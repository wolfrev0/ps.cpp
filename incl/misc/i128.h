#pragma once
#include "core/base.h"

using i128=__int128;
istream& operator>>(istream& s,i128& a){a=input();return s;}
ostream& operator<<(ostream& s,i128 a){
	if(!a){cout<<0;return s;}
	if(a<0)cout<<'-',a*=-1;
	i128 b=1;//rev of a
	while(a)
		b*=10,b+=a%10,a/=10;
	while(b!=1)
		cout<<signed(b%10),b/=10;
	return s;}