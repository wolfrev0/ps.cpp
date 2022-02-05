#!/usr/bin/env bash

#build <*.cpp|*.h> <R|D>

mkdir -p res

src=${1:-"src/main.cpp"}
dbgrel=${2:-"D"}

base_arg=" -iquote ./incl -std=c++2a -Wall -Wno-unused-variable -fconcepts"
if [ $dbgrel == "D" ]; then #debug
	option="-O0 -D DEBUG=1 -ggdb3"
else #release
	option="-O2"
fi

function f(){
	arr=$(g++ $src $base_arg -MM | cut -d ' ' -f2-)
	arr="${arr//\\}"
	if (( 1 < $(echo $arr | wc -w | cat) )); then
		for i in $arr
		do
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
if ! [[ "$2" =~ ?*.h ]]; then
	echo "//[Author]   tuxedcat" > res/submit.cpp
	echo "//[Date]     $(date +%Y.%m.%d)" >> res/submit.cpp
	echo "//[File]     $1" >> res/submit.cpp
	echo "//[Library]  https://github.com/tuxedcat/pslib" >> res/submit.cpp
	echo "#pragma GCC optimize("O3")" >> res/submit.cpp
	awk '//' $(f|tac|grep -Ev "incl/core/debug.h") | grep -Ev '#include *"|#pragma once' >> res/submit.cpp
fi

for i in incl/core/*
do
	if [ "$i" != "$src" ] && [ incl/core/base.h.gch -ot $i ]; then
		g++ incl/core/base.h $base_arg $option
	fi
done

RED='\033[1;31m'
CYAN='\033[1;36m'
GREEN='\033[1;32m'
NONE='\033[0m' # No Color

path_out=res/$(echo ${src##*/} | cut -d'.' -f1)$dbgrel.out
if [ $path_out -ot $src ] || [ $path_out -ot incl/core/base.h.gch ]; then
	echo -e "${CYAN}newly built ($dbgrel)${NONE}"
	g++ $src $base_arg $option -o $path_out
else
	echo -e "${GREEN}up to date ($dbgrel)${NONE}"
fi

if [[ $(cat res/submit.cpp | grep -E "(input.*){2}") ]]; then
	echo -e "${RED}[WARNING]: multiple call input() in one line (beware param eval order)${NONE}"
fi

# std헤더와 매크로 제거하면 아래와 같은 전처리기 활용도 가능하긴 하다.
# g++ src/tpl.cpp -std=c++20 -iquote ./incl -E | grep -Ev '# *'
# 다만 커스텀헤더 안의 std헤더를 제거하는게 좀 귀찮은거같다. 제거한 헤더와 매크로도 제자리 "찾아"서 돌려놓는것도 생각하면 그냥 현재상태가 나은듯