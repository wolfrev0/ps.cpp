#pragma once
#include "core/base.h"

bool ispow2(int n){return (n&-n)==n and n;}
u64 to_mask(int i){return 1ULL<<i;}
int to_num(u64 mask){assert(ispow2(mask));return lg2f(mask);}