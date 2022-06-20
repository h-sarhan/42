PURPLE="\033[0;35m"
SUCCESS="\033[0;32m"
BLUE="\033[0;36m"
YELLOW="\033[0;33m"
RESET="\033[0m"
ERROR="\033[0;31m"

run_test() {
	echo -e "${PURPLE}${1}${RESET}"
	echo "./pipex ${2} ${3} ${4} ${5}"
	echo
	./pipex "${2}" "${3}" "${4}" "${5}" 2> my_err
	echo $? > my_ret
	cat "${5}" > my_out
	(< ${2} ${3} | ${4} > ${5}) 2> bash_err
	echo $? > correct_ret
	cat "${5}" > correct_out
	if cmp -s my_out correct_out
	then
		echo -e "${GREEN}Correct Output${RESET}"
	else
		echo -e "${ERROR}Wrong output${RESET}"
		echo "My Output:"
		cat my_out
		echo "Correct Output:"
		cat correct_out
		echo 
	fi
	if cmp -s my_ret correct_ret
	then
		echo -e "${GREEN}Correct Return Value${RESET}"
	else
		echo -e "${ERROR}Wrong return${RESET}"
		echo "My Return:"
		cat my_ret
		echo "Correct Return:"
		cat correct_ret
		echo 
	fi
	echo -e "${YELLOW}My error${RESET}"
	cat my_err
fi
echo "My return value:" $?
echo
(< infile grep a1 | wc -w > outfile) 2> bash_err
echo "Correct outfile: "
cat -e outfile
echo "Correct return value:" $?
if [ "$(cat bash_err)" != "" ]
then
	echo -e "${YELLOW}Bash error: ${RESET}"
	cat bash_err
fi
echo

echo -e "${SUCCESS}TEST 2${RESET}"
echo -e "${BLUE}Test with invalid infile${RESET}"
echo "./pipex infiled \"grep a1\" \"wc -w\" outfile"
./pipex infiled "grep a1" "wc -w" outfile 2> my_err
echo "My outfile: "
cat -e outfile
if [ "$(cat my_err)" != "" ]
then
	echo -e "${YELLOW}My error: ${RESET}"
	cat my_err
fi
echo "My return value:" $?
echo
(< infiled grep a1 | wc -w > outfile) 2> bash_err
echo "Correct outfile: "
cat -e outfile
if [ "$(cat bash_err)" != "" ]
then
	echo -e "${YELLOW}Bash error: ${RESET}"
	cat bash_err
fi
echo "Correct return value:" $?
echo


echo -e "${SUCCESS}TEST 3${RESET}"
echo -e "${BLUE}Test with invalid cmd_1${RESET}"
echo "./pipex infile \"gerp a1\" \"wc -w\" outfile"
./pipex infile "gerp a1" "wc -w" outfile 2> my_err
echo "My outfile: "
cat -e outfile
if [ "$(cat my_err)" != "" ]
then
	echo -e "${YELLOW}My error: ${RESET}"
	cat my_err
fi
echo "My return value:" $?
echo
(< infile gerp a1 | wc -w > outfile) 2> bash_err
echo "Correct outfile: "
cat -e outfile
if [ "$(cat bash_err)" != "" ]
then
	echo -e "${YELLOW}Bash error: ${RESET}"
	cat bash_err
fi
echo "Correct return value:" $?
echo

echo -e "${SUCCESS}TEST 4${RESET}"
echo -e "${BLUE}Test with invalid cmd_2${RESET}"
echo "./pipex infile \"grep a1\" \"wqc -w\" outfile"
./pipex infile "grep a1" "wqc -w" outfile 2> my_err
echo "My outfile: "
cat -e outfile
if [ "$(cat my_err)" != "" ]
then
	echo -e "${YELLOW}My error: ${RESET}"
	cat my_err
fi
echo "My return value:" $?
echo
(< infile grep a1 | wqc -w > outfile) 2> bash_err
echo "Correct outfile: "
cat -e outfile
if [ "$(cat bash_err)" != "" ]
then
	echo -e "${YELLOW}Bash error: ${RESET}"
	cat bash_err
fi
echo "Correct return value:" $?
echo

echo -e "${SUCCESS}TEST 5${RESET}"
echo -e "${BLUE}Test with readonly outfile${RESET}"
touch readonlyfile
chmod 0444 readonlyfile
echo "./pipex infile \"grep a1\" \"wc -w\" readonlyfile"
./pipex infile "grep a1" "wc -w" readonlyfile 2> my_err
echo "My outfile: "
cat -e readonlyfile
if [ "$(cat my_err)" != "" ]
then
	echo -e "${YELLOW}My error: ${RESET}"
	cat my_err
fi
echo "My return value:" $?
echo
(< infile grep a1 | wc -w > readonlyfile) 2> bash_err
echo "Correct outfile: "
cat -e readonlyfile
if [ "$(cat bash_err)" != "" ]
then
	echo -e "${YELLOW}Bash error: ${RESET}"
	cat bash_err
fi
echo "Correct return value:" $?
echo

