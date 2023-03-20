#pragma once
#include "core/base.h"

// Random

#if SYSCALL_ALLOWED
	mt19937_64 _rng(chrono::system_clock::now().time_since_epoch().count()^i64(new int)^time(0));
#else
	mt19937_64 _rng(1243);
#endif
int rd(){static uniform_int_distribution<int> dist(0,inf<int>());return dist(_rng);}
int rd(int e){return rd()%e;}
int rd(int s,int e){return rd()%(e-s)+s;}
fp rdf(){static uniform_real_distribution<fp> dist(0,1);return dist(_rng);}
void shuffle(auto is,auto ie){shuffle(is,ie,_rng);}
