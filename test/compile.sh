onFail() {
	# rm -f res/_tmp_compile_.cpp
	exit 1;
}
trap onFail ERR

rm -f res/_tmp_compile_.cpp
touch res/_tmp_compile_.cpp
for i in $(find incl -name '*.h' ! -wholename 'incl/testlib.h')
do
	echo '#include "'${i#*incl/}'"' >> res/_tmp_compile_.cpp
done
echo 'signed main(){}' >> res/_tmp_compile_.cpp
tool/build.sh res/_tmp_compile_.cpp D
tool/build.sh res/_tmp_compile_.cpp R
