for i in $(find incl -name '*.h' ! -wholename 'incl/testlib.h')
do
	echo '#include "'${i#*incl/}'"' >> _tmp_compile_.cpp
done
echo 'signed main(){}' >> _tmp_compile_.cpp
tool/build.sh _tmp_compile_.cpp D
tool/build.sh _tmp_compile_.cpp R
rm _tmp_compile_.cpp