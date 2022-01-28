RED='\033[1;31m'
CYAN='\033[1;36m'
GREEN='\033[1;32m'
NONE='\033[0m'
shopt -s nullglob
set -e
trap "echo -e '${RED}FAIL${NONE}'" ERR
for i in test/tc/*.in;
do
	echo "########## "${i%.*}" ##########"
	diff <(res/$1.out<$i) ${i%.*}.ans -BZ
done
echo -e "${GREEN}OK${NONE}"