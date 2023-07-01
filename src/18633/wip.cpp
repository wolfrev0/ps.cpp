#include "core/base.h"
signed main(){
	void solve();
	for(int ti=1,t=input1();ti<=t;ti++)
		// print("Case #",ti,": "),
		solve();
	// assert(cin.get()==' ');
	// assert(cin.get()=='\n');
	// assert(cin.get()==EOF);
}
void solve(){
	auto n=input1();
	Arr<pint> a(n);
	for(auto&[x,y]:a)
		cin>>x>>y;
	func(int,f,int turn){
		// dbg(a);
		if(a.empty())
			return 0;
		if(!turn){
			int xmin=inf<int>();
			int ymin=inf<int>();
			for(auto [x,y]:a){
				if(x>y){
					if((x+y)%2==0 or !y)
						xmin=min(xmin,x-y);
				}else if(x<y){
					if((x+y)%2==0 or !x)
						ymin=min(ymin,y-x);
				}else{
					return 1;
				}
			}
			if(xmin>2){
				Arr<pint> b;
				for(auto [x,y]:a)
					if(x-1>=0)
						b.emplace_back(x-1,y);
				swap(a,b);
				return f(!turn);
			}else if(ymin>2){
				Arr<pint> b;
				for(auto [x,y]:a)
					if(y-1>=0)
						b.emplace_back(x,y-1);
				swap(a,b);
				return f(!turn);
			}else{
				return 1;
			}
		}else{
			Arr<pint> b;
			for(auto [x,y]:a){
				if(x>y){
					if(x-1>=0)
						b.emplace_back(x-1,y);
				}else if(x<y){
					if(y-1>=0)
						b.emplace_back(x,y-1);
				}else{
					//TODO
					if(rand()%2){
						if(x-1>=0)
							b.emplace_back(x-1,y);
					}else{
						if(y-1>=0)
							b.emplace_back(x,y-1);
					}
				}
			}
			swap(a,b);
			return f(!turn);
		}
	};
	println(f(0));
}
