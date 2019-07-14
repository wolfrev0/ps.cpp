#pragma once
#include "Core.h"
#include <sys/stat.h>

struct FIO{
	char* p;
	FIO(){
		struct stat64 z;
		fstat64(0, &z);
		setvbuf(stdout, 0, 0, z.st_blksize);
		p=new char[z.st_size+1];
		cin.read(p, z.st_size+1);
	}
	operator bool(){return *p;}

	FIO& operator>>(char& c){
		do{c=*p++;}while(c==' '||c=='\n');
		return *this;
	}
	template<typename T>
	FIO& operator>>(T& n){
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
	FIO& operator>>(string& s){
		int c=*p++;
		while(c==' '||c=='\n')
			c=*p++;
		while(c&&c!=' '&&c!='\n'){
			s.pb(c);
			c=*p++;
		}
		return *this;
	}
}fcin;
#define cin fcin