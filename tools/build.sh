#!/usr/bin/env bash
src=${1:-"main.cpp"}
mkdir -p ./bin >/dev/null 2>&1
if [ "$2" == "RELEASE" ]; then
	g++ -std=c++17 -O3 -Wall -fconcepts -iquote ./includes -o ./bin/a.out $src
else
	g++ -iquote ./includes -g3 -O0 -D DEBUG -Wall -std=c++17 -fconcepts -o ./bin/a.out $src
fi
./bin/merger.out $src ./includes
