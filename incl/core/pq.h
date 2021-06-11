#pragma once
#define PQ std::priority_queue
template<class T>using PQMax=PQ<T>;
template<class T>using PQMin=PQ<T,vector<T>,greater<T>>;