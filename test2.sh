#!/usr/bin/env bash

touch oa ob
while diff --strip-trailing-cr oa ob; do
	echo 123
	./gen < /dev/null > in
	./a < in > oa
	./b < in > ob
	#python3 py/main.py < in > ob
done
rm oa ob