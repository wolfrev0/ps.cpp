#!/usr/bin/env bash

touch oa ob
while cmp -s oa ob; do
	./gen < /dev/null > in
	./a < in > oa
	./b < in > ob
done
rm oa ob