#!/usr/bin/env bash
if [ "$2" == "RELEASE" ]; then
	g++ -std=c++17 -O3 -Wall -fconcepts -iquote ./includes -o ./bin/a.out $1 && ./bin/merger.out $1 ./includes
else
	g++ -iquote ./includes -g -O0 -D DEBUG -Wall -std=c++17 -fconcepts -o ./bin/a.out $1 && ./bin/merger.out $1 ./includes
fi
