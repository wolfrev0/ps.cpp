#!/usr/bin/env bash
src=${1:-"main.cpp"}
mkdir -p ./bin >/dev/null 2>&1
if [ "$2" == "R" ]; then
	g++ -std=c++17 -O3 -Wall -fconcepts -iquote ./incl -o ./bin/a.out $src
else
	g++ -iquote ./incl -ggdb3 -O0 -D DEBUG -Wall -std=c++17 -fconcepts -o ./bin/a.out $src
fi
./bin/merger.out $src ./incl
