#!/usr/bin/env bash

# while true; do
# 	./gen < /dev/null > in
# 	./a < in #> oa
# done

shopt -s nullglob
for i in tc/*.in;
do
	echo "### "${i%.*}" ###"
	./a.out<$i>${i%.*}.o
	diff ${i%.*}.o ${i%.*}.ans -B -Z
done