PURPLE="\033[0;35m"
SUCCESS="\033[0;32m"
BLUE="\033[0;36m"
ERROR="\033[0;31m"
YELLOW="\033[0;33m"
RESET="\033[0m"
TESTS="tests"

echo -e ${BLUE}"Running shell tests: "${RESET}
./${TESTS} expected > expected
./${TESTS} actual > actual
DIFFOUTPUT=$(diff -a expected actual)
if [ "$DIFFOUTPUT" != "" ]
then
    echo -e ${ERROR}"Shell tests have failed!"${RESET}
	echo -e "Showing diff"
	echo -e "${DIFFOUTPUT}"
else
	echo -e ${SUCCESS}"Shell tests have passed!"${RESET}
fi
