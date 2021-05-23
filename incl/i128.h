#pragma once
#include "core/base.h"

using i128=__int128;
ostream& operator<<(ostream& s,i128 a){
	if(!a){cout<<0;return s;}
	if(a<0)cout<<'-',a*=-1;
	i128 b=0;//rev of a
	while(a)b*=10,b+=a%10,a/=10;
	while(b)cout<<int(b%10),b/=10;
	return s;
}