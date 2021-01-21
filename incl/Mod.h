#pragma once

//클래스 Mod는 생각보다 느리지 않다. 16325 제출기록 참고
template<int m>
struct Mod {
	Mod(i64 n=0) :n((n%m+m)%m){}
	explicit operator int()const{return n;}
	explicit operator bool()const{return !!n;}
	i64 val()const { return n; }

	Mod operator - () const { return -n; }
	Mod operator + (const Mod& b)const { return n + b.val(); }
	Mod operator - (const Mod& b)const { return n - b.val() + m; }
	Mod operator * (const Mod& b)const { return n * b.val(); }
	Mod operator / (const Mod& b)const { return *this * inv(b); }
	Mod operator+= (const Mod& b) { return *this = *this + b; }
	Mod operator-= (const Mod& b) { return *this = *this - b; }
	Mod operator*= (const Mod& b) { return *this = *this * b; }
	Mod operator/= (const Mod& b) { return *this = *this / b; }

	Mod& operator++ () { *this += 1ll; return *this; }
	Mod& operator-- () { *this -= 1ll; return *this; }
	Mod operator++(signed) { auto ret = *this; ++*this; return ret; }
	Mod operator--(signed) { auto ret = *this; --*this; return ret; }

	bool operator==(const Mod& r) const { return n == r.n; }
	bool operator!=(const Mod& r) const { return !(*this == r); }
	bool operator<(const Mod& r) const { return n < r.n; }
private:
	i64 n;

	Mod inv(const Mod &b)const {
		auto res = xgcd(b.val(), -m);
		if (1 % res.g)
			throw "No Mod Inv";
		res.x *= 1 / res.g;
		while (res.x < 0)
			res.x += -m / res.g;
		return res.x;
	}
	tint xgcd(i64 a, i64 b) {
		if (b==0) return {a,1,0};
		auto [g,x,y]=xgcd(b, a%b);
		return {g,y,x-(a/b)*y};
	}
};

template<int m>
ostream& operator<<(ostream& s, const Mod<m>& n) { return s << n.val(); }