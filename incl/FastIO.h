#pragma once
#include "Core.h"
#include <sys/stat.h>

#if !(DEBUG)
struct FIO{
	static const int BUF_SZ=1<<24;
	char *p,*q;
	FIO(){
		struct stat z;
		fstat(0, &z);
		setvbuf(stdout, 0, 0, z.st_blksize);
		
		p=new char[BUF_SZ]; q=p+BUF_SZ;
		cin.read(p, BUF_SZ);
	}
	char get(){
		if(p==q) cin.read(p-=BUF_SZ, BUF_SZ);
		return *p++;
	}
	operator bool(){return *p;}

	FIO& operator>>(char& c){
		do{c=get();}while(c==' '||c=='\n');
		return *this;
	}
	template<typename T>
	FIO& operator>>(T& n){
		n=0;
		bool neg = false; 
		int c=get();
		while(c==' '||c=='\n')
			c=get();
		if (c=='-'){
			neg=true;
			c=get();
		}
		while('0'<=c&&c<='9')
			n=n*10+c-'0', c=get();
		if(neg)
			n *= -1;
		return *this;
	}
	FIO& operator>>(string& s){
		int c=get();
		while(c==' '||c=='\n')
			c=get();
		while(c&&c!=' '&&c!='\n'){
			s.pushb(c);
			c=get();
		}
		return *this;
	}
}fcin;
#define cin fcin
#endif