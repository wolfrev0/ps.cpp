set -e
for i in $(find incl -name '*.h' ! -wholename 'incl/testlib.h')
do
	echo '#include "'${i#*incl/}'"' >> res/_tmp_compile_.cpp
done
echo 'signed main(){}' >> res/_tmp_compile_.cpp
tool/build.sh res/_tmp_compile_.cpp D
tool/build.sh res/_tmp_compile_.cpp R
rm res/_tmp_compile_.cpp
