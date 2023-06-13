#!/usr/bin/env bash
#build <*.cpp|*.h> <R|D>

mkdir -p res
src=${1:-"src/main.cpp"}
dbgrel=${2:-"D"}

base_arg=" -iquote ./incl -std=c++20 -Wall -Wno-unused-variable"
if [ $dbgrel == "D" ]; then #debug
	option="-D DEBUG=1 -O0 -g -fsanitize=address"
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
	awk '//' $(f|tac) | grep -Ev '#include *"|#pragma once' > res/submit.cpp
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
need_rebuild=$( test $path_out -nt $src )$?
for i in $(find incl -name '*.h')
do
	need_rebuild="$(( $need_rebuild + $( test $path_out -nt $i )$? ))"
done
if [[ $need_rebuild > 0 ]]; then
	echo -e "${CYAN}newly built ($dbgrel)${NONE}"
	if g++ $src $base_arg $option -o $path_out; then
		true;
	else
		exit 1;
	fi
else
	echo -e "${GREEN}up to date ($dbgrel)${NONE}"
fi
if ! [[ "$2" =~ ?*.h ]]; then
	cat res/submit.cpp | head -n 11 > res/build0.tmp
	cat res/submit.cpp | tail -n +12 > res/build1.tmp

	echo "//[Author]   tuxedcat" > res/submit.cpp
	echo "//[Date]     $(date "+%Y.%m.%d %H:%M:%S %Z")" >> res/submit.cpp
	echo "//[File]     $1" >> res/submit.cpp
	echo "//[Library]  https://github.com/tuxedcat/ps.cpp" >> res/submit.cpp
	echo "//[Revision] $(git rev-parse HEAD)" >> res/submit.cpp
	# echo "#pragma GCC optimize(\"O3\")" >> res/submit.cpp
	# echo "#pragma GCC target(\"avx2\")" >> res/submit.cpp
	# echo "#define NDEBUG" >> res/submit.cpp

	echo "/* ORIGINAL_MAIN_SOURCE" >> res/submit.cpp
	cat $src >> res/submit.cpp
	echo "*/" >> res/submit.cpp
	cat res/build0.tmp >> res/submit.cpp
	cpp -P res/build1.tmp | clang-format -style=Google >> res/submit.cpp
fi