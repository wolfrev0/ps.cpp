#!/usr/bin/env bash

#build <*.cpp|*.h> <R|D>

src=${1:-"main.cpp"}

base_arg=" -iquote ./incl -std=c++2a -Wall -Wno-unused-variable -fconcepts"
if [ "$2" == "R" ]; then #release
	option="-O2"
else #debug
	option="-O0 -D DEBUG=1 -ggdb3"
	if [ "$src" != "incl/Core.h" ] && [ "incl/Core.h.gch" -ot "incl/Core.h" ]; then
		g++ incl/Core.h $base_arg $option
	fi
fi
g++ $src $base_arg $option

function f(){
	arr=$(g++ $src $base_arg -MM | cut -d ' ' -f2-)
	arr="${arr//\\}"
	if (( 1 < $(echo $arr | wc -w | cat) )); then
		for i in $arr
		do
			echo $i incl/Config.h
			echo $(awk -F'"' '/^#include *"/{print FILENAME, "incl/"$2}' $i)
			z=$(awk -F'"' '/^#include *"/{print "incl/"$2, "incl/"$2}' $i)
			if (( 1 < $(echo $z | wc -w | cat) )); then
				echo $z
			fi
		done | tsort
	else
		echo $src
	fi
}
if ! [[ "$2" =~ ?*.h ]]; then #header
	awk '//' $(f|tac) | grep -Ev '#include *"|#pragma once' > submit.cpp
fi
