#!/usr/bin/env bash

#build <*.cpp|*.h> <R|D|H>

src=${1:-"main.cpp"}

if [ "incl/Core.h.gch" -ot "incl/Core.h" ]; then
	touch incl/Core.h.gch
	build incl/Core.h H
	echo $src
fi

base_arg=$src" -iquote ./incl -std=c++17 -Wall -fconcepts"
if [ "$2" == "R" ]; then #release
	g++ $base_arg -O2
else #debug
	g++ $base_arg -O0 -D DEBUG=1 -ggdb3
fi

function f(){
	arr=$(g++ $base_arg -MM | cut -d ' ' -f2-)
	arr="${arr//\\}"
	if (( 1 < $(echo $arr | wc -w | cat) )); then
		for i in $arr
		do
			echo $(awk -F'"' '/#include *"/{print "incl/"$2, FILENAME}' $i)
			z=$(awk -F'"' '/#include *"/{print "incl/"$2, "incl/"$2}' $i)
			z=$(echo $z | cut -d ' ' -f2- | rev | cut -d ' ' -f2- | rev)
			if (( 1 < $(echo $z | wc -w | cat) )); then
				echo $z
			fi
		done | tsort
	else
		echo $src
	fi
}
if [ "$2" != "H" ]; then #header
	awk '//' $(f) | grep -Ev '#include *"|#pragma once' > submit.cpp
fi