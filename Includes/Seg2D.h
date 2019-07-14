//not my code
//I got this code from BOJ slack, but I forgot who wrote it.

#pragma once
#include "Core.h"

const int L = (1<<10);

struct seg1d {
	int v[2*L];
	void upd (int P, int V) {
		P += L;
		while(P) {
			v[P] += V;
			P /= 2;
		}
	}
	int get (int S, int E) {
		int R = 0;
		S += L; E += L;
		while(S <= E) {
			if(S % 2 == 1) R += v[S++];
			if(E % 2 == 0) R += v[E--];
			S /= 2; E /= 2;
		}
		return R;
	}
};

struct seg2d {
	seg1d v[2*L];
	void upd (int X, int Y, int V) {
		X += L;
		while(X) {
			v[X].upd(Y, V);
			X /= 2;
		}
	}
	int get (int XS, int XE, int YS, int YE) {
		int R = 0;
		XS += L; XE += L;
		while(XS <= XE) {
			if(XS % 2 == 1) R += v[XS++].get(YS, YE);
			if(XE % 2 == 0) R += v[XE--].get(YS, YE);
			XS /= 2; XE /= 2;
		}
		return R;
	}
};
