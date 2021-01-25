#pragma once
#include "Core.h"

struct Range {
	i64 s, e;
	Range(i64 s, i64 e) : s(s), e(e) {}
	Range operator+(const Range& r) const { return {min(s, r.s), max(e, r.e)}; }
	Range operator*(const Range& r) const { return {max(s, r.s), min(e, r.e)}; }
	Range operator+=(const Range& r) { return *this = *this + r; }
	Range operator*=(const Range& r) { return *this = *this * r; }
	i64 size() const { return e - s; }
};