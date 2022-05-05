# MINISHELL-TESTER

RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"

BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"

make -C ../ > /dev/null
cp ../minishell .
chmod 755 minishell

function exec_test()
{
	TEST1=$(echo $@ "; exit" | ./minishell 2>&-)
	ES_1=$?
	TEST2=$(echo $@ "; exit" | bash 2>&-)
	ES_2=$?
	if [ "$TEST1" == "$TEST2" ] && [ "$ES_1" == "$ES_2" ]; then
		printf " $BOLDGREEN%s$RESET" "✓ "
	else
		printf " $BOLDRED%s$RESET" "✗ "
	fi
	printf "$CYAN \"$@\" $RESET"
	if [ "$TEST1" != "$TEST2" ]; then
		echo
		echo
		printf $BOLDRED"Your output : \n%.20s\n$BOLDRED$TEST1\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
		printf $BOLDGREEN"Expected output : \n%.20s\n$BOLDGREEN$TEST2\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	fi
	if [ "$ES_1" != "$ES_2" ]; then
		echo
		echo
		printf $BOLDRED"Your exit status : $BOLDRED$ES_1$RESET\n"
		printf $BOLDGREEN"Expected exit status : $BOLDGREEN$ES_2$RESET\n"
	fi
	echo
	sleep 0.1
}

# ## NON GERER ##

# # exec_test 'cd'
# # exec_test 'cd ; pwd'
# # exec_test 'cd - ; /bin/pwd'

# # exec_test 'export VAR1 VAR2 VAR3 ; cd $VAR1 $VAR2 $VAR3'
# # exec_test 'cd $VAR1 $VAR2 $VAR3'
# # exec_test 'mkdir test_dir ; cd test_dir ; rm -rf ../test_dir ; cd . ; pwd ; cd . ; pwd ; cd .. ; pwd'
# # mkdir a; mkdir a/b; cd a/b; rm -r ../../a; cd .. ; pwd ; unset PWD ; pwd
# # mkdir a; mkdir a/b; cd a/b; rm -r ../../a; cd .. ; pwd

# ## exec_test 'cat /dev/random | head -c 100 | wc -c'
# ## exec_test 'echo "$1TEST"'



# # TESTS QUI PASSENT PAS

exec_test "ls ;; exit"
exec_test "owief ;; exit"
exec_test ';; test'
exec_test 'ls | > file'
exec_test 'ls | < file2'


# TESTS A FAIRE A LA MAIN (ou ne pas melanger)
# '\\"'
# "abc
# "\\""
# "\\'"
exec_test 'unset PATH ; setenv PATH=/bin:/usr/ ; ls'
exec_test ""a  $""
exec_test 'unset PATH ; setenv PATH "/bin:/usr/" ; ls'
exec_test "'a  $'"



# TESTS SUJET DE CORRECTION
exec_test 'foo'
exec_test '/bin/ls -lsF'
exec_test '/bin/ls -l -a -F'
exec_test 'exit'
exec_test 'echo "it works"'
exec_test 'echo it works'
exec_test 'cd /bin/pwd ; /bin/pwd'
exec_test 'cd incs/ ; /bin/pwd'
exec_test 'setenv FOO bar'
exec_test 'setenv FOO=bar'
exec_test 'unsetenv PATH ; ls'
exec_test 'unsetenv PATH ; /bin/ls'
exec_test 'emacs'
exec_test ' 	   '
exec_test '			ls 		-la 	   '



## PARSING
exec_test '| wc'
exec_test '\\>'
exec_test 'echo "\\\\$HOME"'
exec_test 'echo "\\\\\$HOME"'
exec_test "export test=123\' ; echo $test ; echo $test"


## EXEC
exec_test "unset PATH ; echo"
exec_test """"
exec_test "unset PATH ; ls"
exec_test "''"
exec_test "$ARG"
exec_test "> a """
exec_test "> a"


## ESCAPE / $ & DIVERS TEST Sans quotes
exec_test '$USER'
exec_test '\$USER'
exec_test '\\$USER'
exec_test '\\\$USER'
exec_test '\ $USER'
exec_test '\\ $USER'
exec_test '\\\ $USER'
exec_test '$VAR'
exec_test '\$VAR'
exec_test '\\$VAR'
exec_test '\\$VAR'
exec_test '\\\$VAR'
exec_test '\ $VAR'
exec_test '\\ $VAR'
exec_test '\\\ $VAR'
exec_test 'abc'
exec_test '\abc'
exec_test '\\abc'
exec_test '\\\abc'
exec_test '$'
exec_test '$PWD$USER'
exec_test 'Hi$USERok'


## Simple quotes
exec_test "'abc"
exec_test "'abc'"
exec_test "' abc'"
exec_test "'abc '"
exec_test "'\test'"
exec_test "'\\test'"
exec_test "'\\\test'"
exec_test "'\''"
exec_test "'\\''"
exec_test "'\\\''"
exec_test "'\"'"
exec_test "'\\\''"
exec_test "abc\'"
exec_test "'$'"
exec_test "'$  a'"
exec_test "'$PWD$USER'"
exec_test "'Hi$USERok'"
exec_test "'Hi'$USER'ok'"
exec_test "'Hi'$'USERok'"
exec_test "'$USER'"
exec_test "'\$USER'"
exec_test "'\\$USER'"
exec_test "'\\\$USER'"
exec_test "'\ $USER'"
exec_test "'\\ $USER'"
exec_test "'\\\ $USER'"
exec_test "'$VAR'"
exec_test "'\$VAR'"
exec_test "'\\$VAR'"
exec_test "'\\\$VAR'"
exec_test "'\ $VAR'"
exec_test "'\\ $VAR'"
exec_test "'\\\ $VAR'"


## Double quotes
exec_test ""abc""
exec_test "" abc""
exec_test ""abc ""
exec_test ""\test""
exec_test ""\\test""
exec_test ""\\\test""
exec_test ""\'""
exec_test ""\\\'""
exec_test ""\"""
exec_test ""\\\'""
exec_test "abc\""
exec_test ""$""
exec_test ""$  a""
exec_test ""$PWD$USER""
exec_test ""Hi$USERok""
exec_test ""Hi"$USER"ok""
exec_test ""Hi"$"USERok""
exec_test ""$USER""
exec_test ""\$USER""
exec_test ""\\$USER""
exec_test ""\\\$USER""
exec_test ""\ $USER""
exec_test ""\\ $USER""
exec_test ""\\\ $USER""
exec_test ""$VAR""
exec_test ""\$VAR""
exec_test ""\\$VAR""
exec_test ""\\\$VAR""
exec_test ""\ $VAR""
exec_test ""\\ $VAR""
exec_test ""\\\ $VAR""


## ECHO TESTS
exec_test 'echo "$?TEST"'
exec_test 'echo test tout'
exec_test 'echo test      tout'
exec_test 'echo -n test tout'
exec_test 'echo -n -nnn hello -n ; echo a'
exec_test 'echo -n -n -n test tout'
exec_test 'echo'
exec_test '"echo"'
exec_test 'echo -n'
exec_test 'echo -n -nnnn'
exec_test 'echo -n -nnnn -nna'
exec_test 'echo -n -nna ; echo b'
exec_test 'echo -n Salut!'
exec_test 'echo $'
exec_test 'echo $USER'
exec_test 'echo $USER$PWD'
exec_test 'echo $SHLVL$USER$PWD$LOGNAME'
exec_test 'echo $SHLVL\$USER$PWD\\$LOGNAME'
exec_test 'echo ~'
exec_test 'echo ~/'
exec_test 'echo /~'
exec_test '"echo "'


##CD TESTS
exec_test 'cd ~'
exec_test 'mkdir a; cd a; rm -r ../a; cd ../'
exec_test 'export VAR1=1 VAR2=2 VAR3=3 ; cd $VAR1 $VAR2 $VAR3'
exec_test 'mkdir a; chmod 222 a; cd a'
exec_test 'cd ./file'
exec_test 'cd incs'
exec_test 'cd ./incs'
exec_test 'cd /incs'
exec_test 'cd .. ; pwd'
exec_test 'cd /Users ; pwd'
exec_test 'cd .'
exec_test 'cd ../'
exec_test 'cd ~/Desktop'
exec_test 'cd $HOME'


## PIPE TESTS
exec_test 'cat tests/lorem.txt | grep arcu | cat -e'
exec_test 'echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e'
exec_test 'ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls'

# REDIRECTIONS
exec_test 'echo test > ls ; cat ls'
exec_test 'echo test > ls >> ls >> ls ; echo test >> ls; cat ls'
exec_test '> lol echo test lol; cat lol'
exec_test '>lol echo > test>lol>test>>lol>test mdr >lol test >test; cat test'
exec_test 'cat < ls'
exec_test 'cat < ls > ls'
exec_test '< noexist'
exec_test '> exist'
exec_test '< exist'
rm exist
exec_test '> noexist ; ls'
exec_test '> exist ; ls ; cat exist'
exec_test 'cat < in1 > out2 | grep < in2 | head -n 5 > out3 | wc -w'
exec_test 'cat < nimp | wc'
exec_test 'cat > nimp | wc | rev | wc < nimp | rm nimp'
exec_test 'ls >> nimp | wc | cat nimp | rm nimp'


# ENV EXPANSIONS + ESCAPE
exec_test 'echo    $TEST lol $TEST'
exec_test 'echo $TEST $TEST'
exec_test 'echo test     \    test'
exec_test 'echo \"test'
exec_test 'echo $TEST'
exec_test 'echo "$TEST"'
exec_test "echo '$TEST'"
exec_test 'echo "$TEST$TEST$TEST"'
exec_test 'echo "$TEST$TEST=lol$TEST"'
exec_test 'echo "   $TEST lol $TEST"'
exec_test 'echo $TEST$TEST$TEST'
exec_test 'echo $TEST$TEST=lol$TEST""lol'
exec_test 'echo test "" test "" test'
exec_test 'echo "\$TEST"'
exec_test 'echo "$=TEST"'
exec_test 'echo "$"'
exec_test 'echo "$T1TEST"'



# # MULTI TESTS
exec_test 'echo testing multi ; echo "test 1 ; | and 2" ; cat tests/lorem.txt | grep Lorem'


# # SYNTAX ERROR
exec_test '| test'
exec_test 'echo > <'
exec_test 'echo | |'
exec_test '<'
exec_test 'echo bonjour >>> test'
exec_test 'echo bonjour > > out'
exec_test 'ls><abc'
exec_test '> a ls > b < Makefile'
exec_test '<a cat <b <c'
exec_test '> test | echo blabla; rm test'


## EXIT && Ret
exec_test "exit 9223372036854775808"
exec_test "exit -9223372036854775808"
exec_test "exit +9223372036854775808"
exec_test "exit 93372036854775808"
exec_test "exit -94223372036854775808"
exec_test "exit 922337203assadads6854775808"
exec_test "exit -9223372036854775810"
exec_test "exit -92233720368547758106546465464"
exec_test "exit 92233720368547758106546465464"
exec_test "exit 5 | ls"
exec_test "niania ; exit"
exec_test "ls -la | wtf"
exec_test "cd gdhahahad"
exec_test "gdagadgag"
exec_test "exit 42"
exec_test "exit 42 53 68"
exec_test "exit 259"
exec_test "exit 9223372036854775807"
exec_test "exit -9223372036854775808"
exec_test "exit -4"
exec_test "exit wrong"
exec_test "exit wrong_command"
exec_test "ls -Z"
exec_test "ls ; exit"
exec_test "exit ; ls"
exec_test "exit ; lsfwe"
exec_test "exit ;; lsfwe"
exec_test "owief ; exit 5"
exec_test "exit ||| lsfwe"
exec_test "exit 4 ; ls"
exec_test "exit -"
exec_test "exit 1 2 a"
exec_test "exit a 1 2"
exec_test "ls | exit 5exit 5 | ls"
exec_test "ls | exit 5"
exec_test "exit | ls"
exec_test "exit 45 | ls"
exec_test "exit | ijwg ; exit"
exec_test "exit 9 ; exit 90"
exec_test "exit 0"
exec_test "exit 1"
exec_test "exit 256"
exec_test "exit 257"
exec_test "exit 310"
exec_test "exit -310"
exec_test "exit | exit"


## ENV EXPANSIONS
# ENV_SHOW="env | sort | grep -v SHLVL | grep -v _="
# EXPORT_SHOW="export | sort | grep -v SHLVL | grep -v _= | grep -v OLDPWD"
# exec_test 'export ='
# exec_test 'export 1TEST= ;' $ENV_SHOW
# exec_test 'export TEST ;' $EXPORT_SHOW
# exec_test 'export ""="" ; ' $ENV_SHOW
# exec_test 'export TES=T="" ;' $ENV_SHOW
# exec_test 'export TE+S=T="" ;' $ENV_SHOW
# exec_test 'export TEST=LOL ; echo $TEST ;' $ENV_SHOW
# exec_test 'export TEST=LOL ; echo $TEST$TEST$TEST=lol$TEST'
# exec_test 'export TEST=LOL; export TEST+=LOL ; echo $TEST ;' $ENV_SHOW
# exec_test $ENV_SHOW
# exec_test $EXPORT_SHOW
# exec_test 'export TEST="ls       -l     - a" ; echo $TEST ; $LS ; ' $ENV_SHOW

## EXPORT
# exec_test 'export' $ENV_SHOW
# exec_test 'export ""' $ENV_SHOW
# exec_test 'export VAR ; export' $ENV_SHOW
# exec_test 'export "" VAR' $ENV_SHOW
# exec_test 'export VAR1= ; export' $ENV_SHOW
# exec_test 'export VAR1=1 ; export' $ENV_SHOW
# exec_test 'export VAR VAR1 ; export' $ENV_SHOW
# exec_test 'export VAR VAR11=1 VAR1 ; export' $ENV_SHOW
# exec_test 'export VAR VAR= VARR VAR=1 ; export' $ENV_SHOW
# exec_test 'export VAR=$USER ; export' $ENV_SHOW
# exec_test 'export 1VAR 2VAR=' $ENV_SHOW
# exec_test 'export _VAR ; export' $ENV_SHOW
# exec_test 'export *VAR ; export' $ENV_SHOW
# exec_test 'export $VAR=s\ -la ; l$VAR' $ENV_SHOW

## UNSET
# exec_test 'unset' $ENV_SHOW
# exec_test 'unset ""' $ENV_SHOW
# exec_test 'unset VAR ; export' $ENV_SHOW
# exec_test 'unset VAR ""' $ENV_SHOW
# exec_test 'unset VAR1 ; export' $ENV_SHOW
# exec_test 'unset VAR ; export' $ENV_SHOW
# exec_test 'unset VAR1 VAR ; export' $ENV_SHOW
# exec_test 'unset VAR11 ; export' $ENV_SHOW
# exec_test 'unset VAR ; export' $ENV_SHOW
# exec_test 'unset NOEXIST' $ENV_SHOW
# exec_test 'unset 1VAR' $ENV_SHOW
# exec_test 'unset _VAR ; export' $ENV_SHOW
# exec_test 'unset *VAR' $ENV_SHOW
# exec_test 'unset $VAR=s\ -la ; l$VAR' $ENV_SHOW
# exec_test 'unset SHLVL ; bash; export' $ENV_SHOW

# exec_test 'env'
# exec_test 'unsetenv FOO ; env'
# exec_test 'unsetenv FOO ; env ; unsetenv FOO ; env'

rm lol ls file noexist exist out2 out3 a b
rm minishell
