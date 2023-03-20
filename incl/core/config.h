#pragma once
#include "core/std.h"

#define SYSCALL_ALLOWED 1
#if SYSCALL_ALLOWED
	#include <bits/extc++.h>
	#include <ext/rope>
#endif

#define int i64
#define FP_EPS 1e-11
#define COUT_FP 11
using fp=double; //long double,__float128
#define CPP20 1
#define DBG_SETW 3
#define endl '\n' //remove it when interactive