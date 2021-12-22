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
	diff --strip-trailing-cr ${i%.*}.o ${i%.*}.ans
done