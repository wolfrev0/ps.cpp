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
	res/$1.out>test/tc/in
	diff <(res/$2.out<test/tc/in) <(res/$3.out<test/tc/in) -BZ
	echo -e "${GREEN}OK, $i tests${NONE}"
done