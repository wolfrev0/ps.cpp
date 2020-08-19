#!/usr/bin/env bash
src=${1:-"main.cpp"}
mkdir -p ./bin >/dev/null 2>&1
if [ "$2" == "P" ]; then #preprocess
	#g++ -iquote ./incl -std=c++17 -MM main.cpp | 
	#sed -i 's%#include <%//PROTECTED #include <%g' $(find . -name '*.[hc]pp')
else if [ "$2" == "R" ]; then #release
	g++ -iquote ./incl -std=c++17 -O3 -Wall -fconcepts -o ./bin/a.out $src
else #debug
	g++ -iquote ./incl -std=c++17 -O0 -Wall -fconcepts -o ./bin/a.out -ggdb3 -D DEBUG=1  $src
fi
./bin/merger.out $src ./incl
