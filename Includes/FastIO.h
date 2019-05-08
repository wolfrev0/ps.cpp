#pragma once
#include "Core.h"

template<int bufsz>
struct FI{
	char buf[bufsz]={0,};
	char* p=buf;
	FI(){fread_unlocked(buf, sizeof(char), sizeof buf, stdin);}

	 FI& operator>>(char& c){
		do{c=*p++;}while(c==' '||c=='\n');
		return *this;
	}
	template<typename T>
	 FI& operator>>(T& n){
		n=0;
		bool neg = false; 
		int c=*p++;
		while(c==' '||c=='\n')
			c=*p++;
		if (c=='-'){
			neg=true;
			c=*p++;
		}
		while('0'<=c&&c<='9')
			n=n*10+c-'0', c=*p++;
		if(neg)
			n *= -1;
		return *this;
	}
	 FI& operator>>(string& s){
		int c=*p++;
		while(c==' '||c=='\n')
			c=*p++;
		while(c&&c!=' '&&c!='\n'){
			s.push_back(c);
			c=*p++;
		}
		return *this;
	}
	void tie(int x){}
};

template<int bufsz>
struct FO{
	char buf[bufsz]={0,};
	char* p=buf;

	~FO(){fputs_unlocked(buf, stdout);}

	template<typename T>
	 FO& operator<<(T x){return *this;}
	 FO& operator<<(char c){*p++=c;return *this;}
	 FO& operator<<(int n){
		if(n<0)
			*p++='-', n*=-1;
		char buf[10];
		int len=0;
		while(n)
			buf[len++]=n%10+'0', n/=10;
		if(!len)
			*p++='0';
		while(len)
			*p++=buf[--len];
		return *this;
	}
	 FO& operator<<(i64 n){
		if(n<0)
			*p++='-', n*=-1;
		char buf[20];
		int len=0;
		while(n)
			buf[len++]=n%10+'0', n/=10;
		if(!len)
			*p++='0';
		while(len)
			*p++=buf[--len];
		return *this;
	}
	 FO& operator<<( string& s){
		for(auto& c:s)
			*p++=c;
		return *this;
	}
	void tie(int x){}
};