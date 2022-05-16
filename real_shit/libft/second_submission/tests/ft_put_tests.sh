./run_tests putchar 1 > result
./run_tests putchar 2 > expected
diff result expected

./run_tests putstr 1 > result
./run_tests putstr 2 > expected
diff result expected

./run_tests putendl 1 > result
./run_tests putendl 2 > expected
diff result expected

./run_tests putnbr 1 > result
./run_tests putnbr 2 > expected
#diff -a result expected
rm result expected
