echo "MY OUTPUT"
# ../pipex infile "echo \"hi \\\" \" mom and \" \\\" dad\"" cat outfile 
# ../pipex infile "grep love"  "wc -l"  "awk '{printf (\"number of lines that has love is %d\", \$1)}'" outfile
# ../pipex infile "grep \"This love\""  "wc -l"  "awk \"{printf(\\\"number of \\\\\\\"lines that has love is %d\\\",\$1)}\"" outfile
echo $?
echo "SHELL OUTPUT"
# < infile echo "hi \" " mom and " \" dad" | cat > outfile2
# < infile grep love | wc -l | awk '{printf("number of lines that has love is %d", $1)}' > outfile2
# < infile grep "This love" | wc -l | awk "{printf(\"number of \\\"lines that has love is %d\",\$1)}" > outfile2
echo $?