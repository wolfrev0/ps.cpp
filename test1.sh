#!/usr/bin/env bash

# while true; do
# 	./gen < /dev/null > in
# 	./a < in #> oa
# done


for i in {10..143}
do
	./a.out<tests/$i>o$i
	diff --strip-trailing-cr o$i tests/$i.a
done