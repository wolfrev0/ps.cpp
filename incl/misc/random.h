#pragma once
#include "core/base.h"

// Random

const u64 __RANDOM_SEED={
	#if SYSCALL_ALLOWED
		chrono::system_clock::now().time_since_epoch().count()^time(0)^
	#endif
	u64("")
};
mt19937_64 _rng(__RANDOM_SEED);
int rd(){static uniform_int_distribution<int> dist(0,inf<int>());return dist(_rng);}
int rd(int e){return rd()%e;}
int rd(int s,int e){return rd()%(e-s)+s;}
double rdf(){static uniform_real_distribution<double> dist(0,1);return dist(_rng);}
void shuffle(auto is,auto ie){shuffle(is,ie,_rng);}
