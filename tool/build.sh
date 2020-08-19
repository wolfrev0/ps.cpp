#!/usr/bin/env bash
src=${1:-"main.cpp"}
mkdir -p ./bin >/dev/null 2>&1
base_arg=$src" -iquote ./incl -std=c++17 -Wall -fconcepts"
if [ "$2" == "R" ]; then #release
	g++ $base_arg -O0
else #debug
	g++ $base_arg -O2 -D DEBUG=1 -ggdb3
fi
function f(){
	for i in $(g++ $base_arg -MM | cut -d ' ' -f2-)
	do
		echo $(awk -F'"' '/#include *"/{print "incl/"$2, FILENAME}' $i)
	done | tsort
}
awk '//' $(f) | grep -Ev '#include *"|#pragma once' > submit.cpp