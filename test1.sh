#!/usr/bin/env bash

while true; do
	./gen < /dev/null > in
	./a < in #> oa
done