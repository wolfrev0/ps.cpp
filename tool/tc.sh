RED='\033[1;31m'
CYAN='\033[1;36m'
GREEN='\033[1;32m'
NONE='\033[0m'
shopt -s nullglob
# set -e
# trap "echo -e '${RED}FAIL${NONE}'" ERR
test_cnt=$(find test/ -name "*.in" -printf '.' | wc -m)
succ=0
fail=0
input_pattern=test/*.in
answer_pattern=${i%.*}.ans
for i in $input_pattern;
do
	echo "Running "${i%.*}" ("$(( ($succ+$fail)*100/$test_cnt ))"%)"
	if /usr/bin/time -v diff <($1<$i) $answer_pattern -BZ 2> >(awk '/Elap|Max/') 1> >(head -n 4); then
		succ=$((succ+1))
	else
		fail=$(($fail+1))
		fail_list+=$i", ";
	fi
done
echo -e "${GREEN}Ok: $succ tests${NONE}"
if (( $fail )); then
	echo -e "${RED}Fail: $fail tests. [$fail_list] ${NONE}"
	exit 1;
fi
