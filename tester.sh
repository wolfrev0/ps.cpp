#!/usr/bin/env bash

rm o1 o2
while [ $(head -1 o1) = $(head -1 o2) ]; do
	./gen > in
	./a < in > o1
	./b < in > o2
done