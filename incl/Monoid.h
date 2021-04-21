#pragma once
#include "Core.h"

template<class T> struct MonoidPlus {
	cxp static T f(T a, T b) { return a + b; }
	cxp static T id() { return T(0); }
	cxp static T fn(T a, int n) { return a * n; }
	// static_assert(f(id(), id()) == id());
};
template<class T> struct MonoidMin {
	cxp static T f(T a, T b) { return min(a, b); }
	cxp static T id() { return inf<T>(); }
	cxp static T fn(T a, int n) { return a; }
	// static_assert(f(id(), id()) == id());
};
template<class T> struct MonoidMax {
	cxp static T f(T a, T b) { return max(a, b); }
	cxp static T id() { return -inf<T>(); }
	cxp static T fn(T a, int n) { return a; }
	// static_assert(f(id(), id()) == id());
};
template<class T, T _id = inf<T>()> struct MonoidAss {
	cxp static T f(T a, T b) { return b; }
	cxp static T id() { return _id; }
	cxp static T fn(T a, int n) { return a; }
	// static_assert(f(id(), id()) == id());
};
template<class T> struct MonoidXor {
	cxp static T f(T a, T b) { return a ^ b; }
	cxp static T id() { return T(0); }
	cxp static T fn(T a, int n) { return n & 1 ? a : 0; }
	// static_assert(f(id(), id()) == id());
};