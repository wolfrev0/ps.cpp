#!/usr/bin/env bash
set -e
mkdir -p build
src=${1:-"src/main.cpp"}
build_type=${2:-"Debug"}



#########################
#   CREATE submit.cpp   #
#########################
function f(){
	arr=$(g++ $src -iquote ./incl -std=c++20 -Wall -Wno-unused-variable -MM | cut -d ' ' -f2-)
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
awk '//' $(f|tac) | grep -Ev '#include *"|#pragma once' > build/submit.cpp
cat build/submit.cpp | head -n 11 > build/build0.tmp
cat build/submit.cpp | tail -n +12 > build/build1.tmp
echo "//[Author]   tuxedcat" > build/submit.cpp
echo "//[Date]     $(date "+%Y.%m.%d %H:%M:%S %Z")" >> build/submit.cpp
echo "//[File]     $src" >> build/submit.cpp
echo "//[Library]  https://github.com/tuxedcat/ps.cpp" >> build/submit.cpp
echo "//[Revision] $(git rev-parse HEAD)" >> build/submit.cpp
# echo "#pragma GCC optimize(\"O3\")" >> build/submit.cpp
# echo "#pragma GCC target(\"avx2\")" >> build/submit.cpp
# echo "#define NDEBUG" >> build/submit.cpp
echo "/* ORIGINAL_MAIN_SOURCE" >> build/submit.cpp
cat $src >> build/submit.cpp
echo "*/" >> build/submit.cpp
cat build/build0.tmp >> build/submit.cpp
cpp -P build/build1.tmp | clang-format -style=Google >> build/submit.cpp



############################
#   build execution file   #
############################
mkdir -p build/$src/$build_type
cmake -GNinja -Bbuild/$src/$build_type -DSOURCE_PATH=${src} -DCMAKE_BUILD_TYPE=${build_type}
cmake --build build/$src/$build_type 
