#!/usr/bin/env bash

touch o1 o2
while cmp -s o1 o2; do
	./gen > in
	./a < in > o1
	./b < in > o2
done
rm o1 o2