#pragma once
#include "Core.h"

#include <sys/stat.h>

struct FI{
	char* p;
	FI(){
		tie(0);
		struct stat z;
		fstat(0, &z);
		p=new char[z.st_size+1];
		cin.read(p, z.st_size+1);
	}

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
	void tie(void* x){cin.tie(0);}
}fcin;
#define cin fcin