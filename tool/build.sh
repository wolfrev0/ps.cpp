#!/usr/bin/env bash
src=${1:-"main.cpp"}
mkdir -p ./bin >/dev/null 2>&1
base_arg=$src" -iquote ./incl -std=c++17 -Wall -fconcepts"
if [ "$2" == "R" ]; then #release
	g++ $base_arg -O0 -D FASTIO=1
else #debug
	g++ $base_arg -O2 -D DEBUG=1 -ggdb3
fi
function f(){
	for i in $(g++ $base_arg -MM | cut -d ' ' -f2-)
	do
		echo $(awk -F'"' '/#include *"/{print "incl/"$2, FILENAME}' $i)
	done | tsort
}
awk '//' $(f) | grep -Ev '#include *"|#pragma once' > _submit.cpp
grep -E '#include *<' _submit.cpp > submit.cpp
grep -Ev '#include *<' _submit.cpp > __submit.cpp
g++ $base_arg -fdirectives-only -fmax-include-depth=0 __submit.cpp 2> /dev/null >> submit.cpp
rm _submit.cpp __submit.cpp
#awk  -F'#include' '//'
#submit.cpp >> submit.cpp