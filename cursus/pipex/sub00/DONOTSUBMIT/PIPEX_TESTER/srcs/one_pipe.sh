# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    one_pipe.sh                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/15 14:44:49 by ael-bekk          #+#    #+#              #
#    Updated: 2022/06/26 08:34:38 by hsarhan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/zsh

l1="======================================================================================="
l2="---------------------------------------------------------------------------------------"
GREEN="\033[38;2;57;181;74m"
RED="\033[38;2;222;56;43m"
BLUE="\033[38;2;34;183;235m"
YELLOW="\033[38;2;255;176;0m"
PURPLE="\033[38;2;255;105;180m"
WHITE="\033[1;37m"
RESET="\033[0m"


echo "\n\n\n\n${GREEN}test your pipex with one pipe :${RESET}"
echo "$RED$l2$RESET"

make fclean -C ..

echo "${YELLOW}[make] :${RESET} your pipex : ${PURPLE}Mandatory${RESET}"
make -C ../
echo "$RED$l2$RESET"

if ! [ -f "$1" ]
then
	echo "${YELLOW}Error :${RESET} No such file or directory: ${PURPLE}pipex${RESET}\n" >&2 ; exit
fi

echo "sgfefeqd qwdqwdddafasd s+64 65 30 9 2 92 ad asd asd as d asd\n asdasd a dasd sd \n asdasd asdasd asd asd\n asdqpkqwd ew eqckqwxqwx qw \n qfqwodeqm domw	m	\tefeqc eqew cewx ewc ewc ewc wc ew" > in_file


timeout() {
    ( $1 "$2" "$3" "$4" "$5" 2> /dev/null ) & pid=$!
    ( sleep 3 && kill -HUP $pid ) 2>/dev/null & watcher=$!
    if wait $pid 2>/dev/null; then
        status="finished"
        pkill -HUP -P $watcher
        wait $watcher
    else
        status="interrupted"
    fi
}

timeout2() {
    ( $1 "$2" "$3" "$4" "$5" 2> /dev/null ) & pid=$!
    ( sleep 10 && kill -HUP $pid ) 2>/dev/null & watcher=$!
    if wait $pid 2>/dev/null; then
        status="finished"
        pkill -HUP -P $watcher
        wait $watcher
    else
        status="interrupted"
    fi
}


echo "${PURPLE}==============>Test 1${RESET}"
printf "${WHITE}\tcat /dev/random | head -n 5                                     : ${RESET}"
timeout "$1" "in_file" "cat /dev/random" "head -n 5" "outfile"
if [ "$status" = "finished" ]
    then
    echo "${GREEN}[OK]${RESET}\n"
else
    echo "${RED}[KO]${RESET}\n"
fi
sleep 0.7

echo "${PURPLE}==============>Test 2${RESET}"
printf "${WHITE}\tcat /dev/random | /usr/bin/tail -n 5                            : ${RESET}"
timeout "$1" "in_file" "cat /dev/random" "/usr/bin/tail -n 5" "outfile"
if [ "$status" = "interrupted" ]
    then
    echo "${GREEN}[OK]${RESET}\n"
else
    echo "${RED}[KO]${RESET}\n"
fi
sleep 0.7

echo "${PURPLE}==============>Test 3${RESET}"
printf "${WHITE}\tcat /dev/random | wc                                            : ${RESET}"
timeout "$1" "in_file" "cat /dev/random" "wc" "outfile"
if [ "$status" = "interrupted" ]
    then
    echo "${GREEN}[OK]${RESET}\n"
else
    echo "${RED}[KO]${RESET}\n"
fi
sleep 0.7

echo "${PURPLE}==============>Test 4${RESET}"
printf "${WHITE}\tcat | wc -cl                                                    : ${RESET}"
timeout "$1" "in_file" "cat" "wc -cl" "outfile"
< in_file cat | wc -cl > outfile2
different=`diff outfile outfile2`
if [ "$status" = "finished" ] && [ "$different" = "" ]
    then
    echo "${GREEN}[OK]${RESET}\n"
else
    echo "${RED}[KO]${RESET}\n"
fi
sleep 0.7

echo "${PURPLE}==============>Test 5${RESET}"
timeout "$1" "in_file" "/bin/cat" "wc -cl" "outfile"
< in_file /bin/cat | wc -cl > outfile2
different=`diff outfile outfile2`
printf "${WHITE}\t/bin/cat | wc -cl                                               : ${RESET}"
if [ "$status" = "finished" ] && [ "$different" = "" ]
    then
    echo "${GREEN}[OK]${RESET}\n"
else
    echo "${RED}[KO]${RESET}\n"
fi
sleep 0.7


echo "${PURPLE}==============>Test 6${RESET}"
printf "${WHITE}\tsleep 9 | sleep 4                                               : ${RESET}"
SECONDS=0;
timeout2 "$1" "in_file" "sleep 9" "sleep 4" "outfile"
if [ "$status" = "finished" ] && [ "$SECONDS" -eq "9" ]
    then
    echo "${GREEN}[OK]${RESET}\n"
else
    echo "${RED}[KO]${RESET}\n"
fi
sleep 0.7

echo "${PURPLE}==============>Test 7${RESET}"
timeout "$1" "in_file" "/bin/cat" "/bin/ls -ls ../" "outfile"
< in_file /bin/cat | /bin/ls -ls ../ > outfile2
different=`diff outfile outfile2`
printf "${WHITE}\t/bin/cat  | /bin/ls -ls                                         : ${RESET}"
if [ "$status" = "finished" ] && [ "$different" = "" ]
    then
    echo "${GREEN}[OK]${RESET}\n"
else
    echo "${RED}[KO]${RESET}\n"
fi

echo "${PURPLE}==============>Test 8${RESET}"
printf "${WHITE}\t./srcs/a.out  | cat                                             : ${RESET}"
timeout "$1" "in_file" ./srcs/a.out "cat" "outfile"
< in_file ./srcs/a.out | cat > outfile2
different=`diff outfile outfile2`
if [ "$status" = "finished" ] && [ "$different" = "" ]
    then
    echo "${GREEN}[OK]${RESET}\n"
else
    echo "${RED}[KO]${RESET}\n"
fi

echo "${PURPLE}==============>Test 9${RESET}"
printf "${WHITE}\tsrcs/a.out  | cat                                               : ${RESET}"
timeout "$1" "in_file" srcs/a.out "cat" "outfile"
< in_file srcs/a.out | cat > outfile2
different=`diff outfile outfile2`
if [ "$status" = "finished" ] && [ "$different" = "" ]
    then
    echo "${GREEN}[OK]${RESET}\n"
else
    echo "${RED}[KO]${RESET}\n"
fi