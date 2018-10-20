#include "Geometry.h"

void error()
{
	cout << -1 << endl;
	exit(0);
}

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	ld res = 0;
	Vec2 sq[4];
	forh(i, 0, 4)
		cin >> sq[i].x >> sq[i].y;

	Polygon cp;
	for (int i = 0; i<4; i++)
	{
		try
		{
			auto res = Line(Vec2(-1000, 0.5), Vec2(1000, 0.5)).intersect(Segment(sq[i], sq[(i + 1) % 4]));
			if (res != err)
				cp.pushback(res);
		}
		catch (...) {}
	}
	for (auto i : sq) {
		if (i.y >= 0.5)
			cp.pushback(i);
	}
	cp.sort();
	res += 6 * cp.area();

	cp.clear();
	for (int i = 0; i<4; i++)
	{
		try
		{
			auto res = Line(Vec2(-1000, -0.5), Vec2(1000, -0.5)).intersect(Segment(sq[i], sq[(i + 1) % 4]));
			if (res != err)
				cp.pushback(res);
		}
		catch (...) {}
	}
	for (auto i : sq) {
		if (i.y <= -0.5)
			cp.pushback(i);
	}
	cp.sort();
	res += 1 * cp.area();

	cp.clear();
	for (int i = 0; i<4; i++)
	{
		try
		{
			auto res = Line(Vec2(0.5, -1000), Vec2(0.5, 1000)).intersect(Segment(sq[i], sq[(i + 1) % 4]));
			if (res != err)
				cp.pushback(res);
		}
		catch (...) {}
	}
	for (auto i : sq) {
		if (i.x >= 0.5)
			cp.pushback(i);
	}
	cp.sort();
	res += 3 * cp.area();

	cp.clear();
	for (int i = 0; i<4; i++)
	{
		try
		{
			auto res = Line(Vec2(-0.5, -1000), Vec2(-0.5, 1000)).intersect(Segment(sq[i], sq[(i + 1) % 4]));
			if (res != err)
				cp.pushback(res);
		}
		catch (...) {}
	}
	for (auto i : sq) {
		if (i.x <= -0.5)
			cp.pushback(i);

	}
	cp.sort();
	res += 4 * cp.area();

	res += 5 * 5 * 4;
	res /= (5 * 5 * 5) - 1;
	res *= 5;
	cout << res << endl;

	return 0;
}