RED='\033[1;31m'
CYAN='\033[1;36m'
GREEN='\033[1;32m'
NONE='\033[0m'

ulimit -s 1048576 && res/${1}.out<test/tc/in
