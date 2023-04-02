#pragma once
#include "geom/segment.h"

template<class T> struct Polygon{
	Arr<Vec2<T>> vtx;

	Polygon(){}
	explicit Polygon(int n):vtx(n){}
	explicit Polygon(const Arr<Vec2<T>>& v):vtx(v){}
	int size()const{ return sz(vtx);}
	void push_back(const Vec2<T>& v){ vtx.emplace_back(v);}
	Vec2<T>& operator[](int idx){ return vtx[idx];}

	fp area(){
		fp ans=0;
		for(int i=1;i<size()-1;i++) ans += vtx[0].cross(vtx[i],vtx[i+1]);
		return ans/2;
	}

	Arr<Segment<T>> to_segments()const{
		Arr<Segment<T>> ret;
		for(int i=0;i<sz(vtx);i++)
			ret.emplace_back(vtx[i],vtx[(i+1)%sz(vtx)]);
		return ret;
	}

	virtual int contains(const Vec2<T>& v)const{
		auto arr=to_segments();
		for(auto i:arr)
			if(i.contains(v)) return true;
		int cnt=0;
		auto l=Segment<T>(v,v+Vec2<T>(int(1e9+9),1));
		for(auto i:arr){
			try{
				i.intersect(l);
				cnt++;
			}catch(...){
			}
		}
		return cnt%2;
	}

	Polygon intersect(const Polygon& r)const{
		// see jongman book geometry
		throw 0;
	}
};

template<class T> struct ConvexPolygon:public Polygon<T>{
	using Polygon<T>::vtx;
	using Polygon<T>::contains;
	using Polygon<T>::to_segments;
	ConvexPolygon():Polygon<T>(){}
	explicit ConvexPolygon(int n):Polygon<T>(n){}
	explicit ConvexPolygon(const Arr<Vec2<T>>& v):Polygon<T>(v){ normalize();}

	// graham scan
	void normalize(){
		if(vtx.empty())return;
		auto me=*min_element(vtx.begin(),vtx.end());
		sort(vtx.begin(),vtx.end(),lam(Vec2<T>::cmpccw(a,b,me),auto&a,auto&b));
		Arr<Vec2<T>> res;
		for(int i=0;i<sz(vtx);i++){
			while(sz(res)>=2){
				auto ltop=res[sz(res)-1]-res[sz(res)-2];
				auto lcandi=vtx[i]-res[sz(res)-2];
				if(ltop.cross(lcandi)<=0) res.pop_back();
				else
					break;
			}
			res.emplace_back(vtx[i]);
		}
		vtx=res;
	}

	//inside: 1
	//edge: 0
	//outside: -1
	int contains(const Vec2<T>& p) const override{
		int s=1, e=sz(vtx)-1, ans=0;
		while (e-s>1){
			int m=(e+s)/2;
			if (cross(vtx[0],vtx[m],p)<0) e=m;
			else s=m;
		}
		T r0 = cross(vtx[0], vtx[s], vtx[e]),
			r1 = cross(vtx[0], vtx[s], p),
			r2 = cross(vtx[0], p, vtx[e]),
			r3 = cross(p, vtx[s], vtx[e]),
			r4 = cross(vtx[0], vtx[1], p),
			r5 = cross(vtx[0], vtx[-1], p);
		if (r0==abs(r1)+abs(r2)+abs(r3) && r3 && r4 && r5)return 1;
		else if	(r3==0 && boxed({vtx[s],vtx[e]}, p)) return 0;
		else if	(r4==0 && boxed({vtx[0],vtx[1]}, p)) return 0;
		else if	(r5==0 && boxed({vtx[0],vtx[-1]}, p)) return 0;
		else return -1;
	}

	Polygon<T> intersect(const Polygon<T>& r)const{
		throw "Unimplemented";
		// Arr<Vec2<T>> ret;
		// //퇴화케이스 처리
		// if(sz(r)<sz(*this))return r.intersect(*this);
		// if(sz(*this)==1){
		// 	if(sz(r)==1 and vtx[0]==r.vtx[0]) ret.emplace_back(vtx[0]);
		// 	else if(sz(r)==2 and Segment<T>(r.vtx[0],r.vtx[1]).contains(vtx[0])) ret.emplace_back(vtx[0]); 
		// }else if(sz(*this)==2){
		// 	if(sz(r)==1 and Segment<T>(vtx[0],vtx[1]).contains(r.vtx[0])) ret.emplace_back(r.vtx[0]);
		// 	else if(sz(r)==2 and Segment<T>(vtx[0],vtx[1]).intersect_det({r.vtx[0],r.vtx[1]})) ret.emplace_back(inf<int>(),inf<int>());
		// }else{
		// 	for(auto i:vtx)
		// 		if(r.contains(i))
		// 			ret.emplace_back(i);
		// 	for(auto i:r.vtx)
		// 		if(contains(i))
		// 			ret.emplace_back(i);
		// }
		// auto s1=to_segments();
		// auto s2=r.to_segments();
		// for(auto i:s1)
		// 	for(auto j:s2){
		// 		try{
		// 			Vec2<T> res;
		// 			if(i.intersect(j,res)) ret.emplace_back(res);
		// 		} catch(...){}
		// 	}
		// return ConvexPolygon(ret);
	}
};
