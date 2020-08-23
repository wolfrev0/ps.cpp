#!/usr/bin/env bash

#build <*.cpp|*.h> <R|D|H>

src=${1:-"main.cpp"}
#mkdir -p ./bin >/dev/null 2>&1
base_arg=$src" -iquote ./incl -std=c++17 -Wall -fconcepts"
if [ "$2" == "R" ]; then #release
	g++ $base_arg -O2
else #debug
	g++ $base_arg -O0 -D DEBUG=1 -ggdb3
fi

function f(){
	arr=$(g++ $base_arg -MM | cut -d ' ' -f2-)
	cnt=$(echo $arr | wc -w | cat)
	if (( 1 < cnt )); then
		for i in $arr
		do
			echo $(awk -F'"' '/#include *"/{print "incl/"$2, FILENAME}' $i)
		done | tsort
	else
		echo $src
	fi
}
if [ "$2" != "H" ]; then #header
	awk '//' $(f) | grep -Ev '#include *"|#pragma once' > submit.cpp
fi