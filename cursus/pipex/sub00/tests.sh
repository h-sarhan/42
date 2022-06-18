PURPLE="\033[0;35m"
SUCCESS="\033[0;32m"
BLUE="\033[0;36m"
YELLOW="\033[0;33m"
RESET="\033[0m"

make

echo -e "${SUCCESS}TEST 1${RESET}"
echo -e "${BLUE}Test with valid parameters${RESET}"
echo "./pipex infile \"grep a1\" \"wc -w\" outfile"
./pipex infile "grep a1" "wc -w" outfile 2> my_err
echo "My outfile: "
cat -e outfile
if [ "$(cat my_err)" != "" ]
then
	echo -e "${YELLOW}My error: ${RESET}"
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

