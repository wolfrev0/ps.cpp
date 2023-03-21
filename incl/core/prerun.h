#pragma once
#include "core/std.h"
#include "core/config.h"

//Pre-runs
auto __PR=(cout<<fixed<<setprecision(COUT_FP),0);
#if !(DEBUG)
auto __PR_NDB=(ios::sync_with_stdio(0),cin.tie(0),cout.tie(0));
#endif
