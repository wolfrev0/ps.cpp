#pragma once
#include "core/std.h"
#define SYSCALL_ALLOWED 1
#if SYSCALL_ALLOWED
	#include <bits/extc++.h>
	#include <ext/rope>
#endif

#define int i64
using fp=double; //long double,__float128
#define COUT_FP 10
#define FP_EPS 1e-11

#define CPP20 1
#define DBG_SETW 3
#define CHECK_INPUT 1

// Frequently used options
#define endl '\n' // Remove it when interactive
#define TC 1 //get<0>(input()) //1
#define TC_OUT_PREFIX //"Case #",ti,": "
