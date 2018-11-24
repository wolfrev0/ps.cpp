#pragma once
#include "Core.h"

struct Frac
{
	ll a, b;
	bool operator<(const Frac &r)const { return a * r.b < r.a*b; }
};