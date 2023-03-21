#pragma once
#include "core/abbr.h"
#include "core/arr.h"
#include "core/config.h"
#include "core/consts.h"
#include "core/debug.h"
#include "core/func1.h"
#include "core/func2.h"
#include "core/prerun.h"
#include "core/std.h"
void solve();
signed main(){
	for(int ti=1,t=TC;ti<=t;ti++)
		print(TC_OUT_PREFIX),
		solve();
	assert(cin.get()=='\n');
	assert(cin.get()==EOF);
}
//
