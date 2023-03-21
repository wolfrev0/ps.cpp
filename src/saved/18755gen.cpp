#include "core/base.h"
#include "misc/gen.h"

void solve(){
	println(1);
	int n=5,k=3,max_len=10;
	println(n,' ',k);
	for(auto [u,v]:gen::tree(n))
		println(u+1,' ',v+1,' ',rd(max_len));
}
