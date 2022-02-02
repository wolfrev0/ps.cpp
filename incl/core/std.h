#pragma once
#include <bits/stdc++.h>
#define _EXT_CODECVT_SPECIALIZATIONS_H 1
#define _EXT_ENC_FILEBUF_H 1
#include <bits/extc++.h>
using namespace std;

#if !(CPP20)
	#define countl_zero(x) __builtin_clzll(x)
	#define popcount(x) __builtin_popcountll(x)
	#define bit_ceil(x) 1<<clg2(x)
#endif