//not my code (출처불명)

#pragma once
#include "core/base.h"

struct seg2d {
	static const int N = 1 << 10;
	struct Seg {
		int tr[2 * N];
		void upd(int i, int v) {
			for(i += N; i; i /= 2) tr[i] += v;
		}
		int get(int s, int e) {
			int r = 0;
			for(s += N, e += N; s <= e; s /= 2, e /= 2) {
				if(s % 2) r += tr[s++];
				if(e % 2 == 0) r += tr[e--];
			}
			return r;
		}
	} tr[2 * N];

	void upd(int x, int y, int v) {
		for(x += N; x; x /= 2) tr[x].upd(y, v);
	}

	int get(int xs, int xe, int ys, int ye) {
		int r = 0;
		for(xs += N, xe += N; xs <= xe; xs /= 2, xe /= 2) {
			if(xs % 2) r += tr[xs++].get(ys, ye);
			if(xe % 2 == 0) r += tr[xe--].get(ys, ye);
		}
		return r;
	}
};
