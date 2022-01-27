#!/bin/bash

# HEADER=all_headers.h
# echo "#ifndef __ALL_HEADERS__" > $HEADER
# echo "#define __ALL_HEADERS__" >> $HEADER
# for file in incl/*.h
# do
#     echo "#include <$file>" >> $HEADER
# done
# echo "#endif" >> $HEADER

for i in $(find incl -name '*.h' ! -wholename 'incl/testlib.h')
do
	echo '#include "'${i#*incl/}'"' >> _tmp_compile_.cpp
done
echo 'signed main(){}' >> _tmp_compile_.cpp
tool/build.sh _tmp_compile_.cpp
tool/build.sh _tmp_compile_.cpp R
rm _tmp_compile_.cpp