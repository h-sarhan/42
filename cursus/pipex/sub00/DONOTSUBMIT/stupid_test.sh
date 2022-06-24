
# SECONDS=0;
# (./pipex infile "sleep 1"  "sleep  7"  "sleep 8"  "sleep 4"  "sleep 5"  "sleep 2"  outfile 2> /dev/null) & pid=$!
# ( sleep 10 && kill -HUP $pid ) 2>/dev/null & watcher=$!
# if wait $pid 2>/dev/null; then
# 	echo finished
# 	echo "SECONDS==$SECONDS"
# 	pkill -HUP -P $watcher
# 	wait $watcher
# else
# 	echo interrupted
# fi

timeout() {
    ( $1 "$2" "$3" "$4" "$5" ) 2> my_error & pid=$!
    # ( infile < cafat | sdfwc -cl > outfile ) 2> my_error & pid=$!
    ( sleep 10 && kill -HUP $pid ) 2>/dev/null & watcher=$!
    if wait $pid 2>/dev/null; then
		echo "my exit code" $?
        status="finished"
		echo $status
        pkill -HUP -P $watcher
        wait $watcher
    else
		echo "exit code" $?
        status="interrupted"
		echo $status
    fi
	# wait $pid
}
# infile < cafat | sdfwc -cl > outfile
# echo "actual exit code" $?
# timeout "./pipex" "infile" "cafat" "sdfwc -cl" "outfile"
# find_smae_err=`cat my_error | grep -a "command not found\|Command not found" | wc -l`
# echo $find_smae_err

# timeout
timeout "./pipex" "in_fisdle" "/bin/catsdc" "wcss -cl" "outfile"
find_smae_err=`cat my_error | grep -a "no such file or directory\|No such file or directory" | wc -l`
find_smae_err2=`cat my_error | grep "command not found\|Command not found" | wc -l`
echo $status $find_smae_err $find_smae_err2
if [ "$status" = "finished" ] && [ "$find_smae_err" -eq "1" ] && [ "$find_smae_err" -eq "1" ]
    then
    echo "${GREEN}[OK]${RESET}\n"
else
    echo "${RED}[KO]${RESET}\n"
fi