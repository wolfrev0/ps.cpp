#pragma once

//Pre-runs
#if !(DEBUG)
auto __PR1=(ios::sync_with_stdio(0),cin.tie(0),cout.tie(0));
#endif
auto& __PR2=(cout<<fixed<<setprecision(COUT_FP));