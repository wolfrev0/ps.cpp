#usage: stress.sh [gen] [src1] [src2]
#examples
#RTE 체크: stress.sh genR mysolR mysolR
#diff 체크: stress.sh genR mysolD correctR

RED='\033[1;31m'
CYAN='\033[1;36m'
GREEN='\033[1;32m'
NONE='\033[0m'

i=0

while $1>test/in && $2<test/in>/tmp/__stress_1.tmp && $3<test/in>/tmp/__stress_2.tmp && diff /tmp/__stress_1.tmp /tmp/__stress_2.tmp -BZ; do
	echo -e "${GREEN}OK, $((++i)) tests${NONE}"
done
echo -e "${RED}FAIL${NONE}"
