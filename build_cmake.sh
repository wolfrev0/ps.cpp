set -e

src=src/b.cpp
build_type=Release
exec_file=build/b.cpp.Release

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
awk '//' $(f|tac) | grep -Ev '#include *"|#pragma once' > res/submit.cpp
cat res/submit.cpp | head -n 11 > res/build0.tmp
cat res/submit.cpp | tail -n +12 > res/build1.tmp

echo "//[Author]   tuxedcat" > res/submit.cpp
echo "//[Date]     $(date "+%Y.%m.%d %H:%M:%S %Z")" >> res/submit.cpp
echo "//[File]     $src" >> res/submit.cpp
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



############################
#   build execution file   #
############################
mkdir -p build
pushd build
cmake .. -DSOURCE_PATH=${src} -DCMAKE_BUILD_TYPE=${build_type} -GNinja
cmake --build .
popd
./$exec_file < test/in