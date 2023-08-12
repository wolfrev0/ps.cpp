#pragma once
#include "core/std.h"
#pragma GCC diagnostic ignored "-Wparentheses"
#define SYSCALL_ALLOWED 1
#if SYSCALL_ALLOWED
	#include <bits/extc++.h>
	#include <ext/rope>
#endif

#define int i64
using fp=double; //long double,__float128
#define COUT_FP 10
#define FP_EPS 1e-11
#define DBG_SETW 3
