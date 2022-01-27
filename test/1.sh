#!/usr/bin/env bash

# while true; do
# 	./gen < /dev/null > in
# 	./a < in #> oa
# done

# for i in {10..143}
# do
# 	./a.out<tests/$i>o$i
# 	diff --strip-trailing-cr o$i tests/$i.a
# done

i=0
while ./gen>in&&./a.out<in; do
	((i++))
	if [ $(($i%100)) -eq 0 ]; then
		echo OK: $i tests
	fi
done
echo FAILED