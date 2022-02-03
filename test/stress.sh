#usage: stress.sh [gen] [src1] [src2]
#examples
#RTE 체크: stress.sh genR mysolR mysolR
#diff 체크: stress.sh genR mysolD correctR
RED='\033[1;31m'
CYAN='\033[1;36m'
GREEN='\033[1;32m'
NONE='\033[0m'
set -e
trap "echo -e '${RED}FAIL${NONE}'" ERR
for((i=0;;++i));do
	$1>test/tc/in
	diff <($2<test/tc/in) <($3<test/tc/in) -BZ
	echo -e "${GREEN}OK, $i tests${NONE}"
done