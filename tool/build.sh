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
	awk '//' $(f|tac|grep -Ev "incl/core/debug.h") | grep -Ev '#include *"|#pragma once' > res/submit.cpp
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

# 일단 표준라이브러리 include문 제거하면 아래와 같은 전처리기 활용도 가능하긴 하다.
# g++ src/tpl.cpp -std=c++20 -iquote ./incl -E | grep -Ev '# *'
# 다만 이거쓰면 매크로도 전부 풀어버려서 코드가 좀 길어지는 단점이 있는듯.
# 제출과 코드저장을 분리하면 쓸만할지도 모르겠지만 지금은 build.sh로 충분한거같다.