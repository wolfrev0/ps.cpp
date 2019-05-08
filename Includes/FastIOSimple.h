#pragma once
#include "Core.h"

#define getchar getchar_unlocked
#define putchar putchar_unlocked

struct FI{
	const FI& operator>>(char& c)const{
		do{c=getchar();}while(c==' '||c=='\n');
		return *this;
	}
	template<typename T>
	const FI& operator>>(T& n)const{
		n=0;
		bool neg = false; 
		int c=getchar();
		while(c==' '||c=='\n')
			c=getchar();
		if (c=='-'){
			neg=true;
			c=getchar();
		}
		while('0'<=c&&c<='9')
			n=n*10+c-'0', c=getchar();
		if(neg)
			n *= -1;
		return *this;
	}
	const FI& operator>>(string& s)const{
		int c=getchar();
		while(c==' '||c=='\n')
			c=getchar();
		while(c!=EOF&&c!=' '&&c!='\n'){
			s.push_back(c);
			c=getchar();
		}
		return *this;
	}
	void tie(int x){}
}fcin;

struct FO{
	template<typename T>
	const FO& operator<<(T x)const{return *this;}
	const FO& operator<<(char c)const{putchar(c);return *this;}
	const FO& operator<<(int n)const{
		if(n<0)
			putchar('-'), n*=-1;
		char buf[10];
		int len=0;
		while(n)
			buf[len++]=n%10+'0', n/=10;
		if(!len)
			putchar('0');
		while(len)
			putchar(buf[--len]);
		return *this;
	}
	const FO& operator<<(i64 n)const{
		if(n<0)
			putchar('-'), n*=-1;
		char buf[20];
		int len=0;
		while(n)
			buf[len++]=n%10+'0', n/=10;
		if(!len)
			putchar('0');
		while(len)
			putchar(buf[--len]);
		return *this;
	}
	const FO& operator<<(const string& s)const{
		for(auto& c:s)
			putchar(c);
		return *this;
	}
	void tie(int x){}
}fcout;

#define cin fcin
#define cout fcout