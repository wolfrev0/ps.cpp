#pragma once
#include "core/base.h"

// Random
mt19937 _rng(i64(new int)^time(0));
int rd(){static uniform_int_distribution<int> dist(0,inf<int>());return dist(_rng);}
int rd(int e){return rd()%e;}
int rd(int s,int e){return rd()%(e-s)+s;}
f64 rdf(){static uniform_real_distribution<f64> dist(0,1);return dist(_rng);}
void shuffle(auto is,auto ie){shuffle(is,ie,_rng);}
