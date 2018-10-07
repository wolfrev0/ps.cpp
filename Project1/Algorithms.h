#pragma once
#include "Core.h"

ll fibo(int n)
{
	static ll memo[100];

	if (n <= 1)
		return 1;
	auto &ret = memo[n];
	if (ret)
		return ret;
	return ret = fibo(n - 1) + fibo(n - 2);
}