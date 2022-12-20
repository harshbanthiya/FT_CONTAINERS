  <h3 align="left">FT_CONTAINERS</h3>

  <p align="left">
    <a href="https://github.com/harshbanthiya/Minishell">
    <img src="https://badge42.vercel.app/api/v2/cl2xrmmu4000609mlo05k9qg8/project/2371023" alt="ft_containers">
    </a>
 </p>
  
   ``Executable Name`` | ./mine.out 
   :--------------- | :---------------
   ``Program Purpose`` | Making a small reimplementation of STL containers vector, map, stack and set
   ``Program Language`` | C++ |
   ``Allowed External Library`` | readline 
   ``Allowed Functions & System Calls`` | printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit,getcwd, chdir, stat, lstat, fstat, unlink, execve,dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
   ``Tested Primarily on`` | MacOs    



## Table of contents

- [Usage](#Usage)
- [What's included](#whats-included)
- [Our Implementation of Built-in Functions](#Built-ins-and-their-Test-Cases)
- [Bug Issues](#bug-issues)
- [Creators](#creators)
- [Request Codebase or explanations](#request-codebase)


## Usage

**To mimic Bash and it's usage for a single command**
```sh
bash -c "Command"
```
```sh
./minishell -c "Command"
```
**Or simply run the executable like bash**
```sh
bash
```
```sh
./minishell 
```
**To Exit**
```sh
ctrl + D
```
**Or**
```sh
./minishell
exit
```


## What's included

**Pipes** 

```sh
./minishell -c "echo oui | cat -e"
./minishell -c "echo test | cat -e | cat -e | cat -e"
./minishell -c "cat Makefile | grep "FLAGS" | grep "FLAGS" | cat -e"
```

**Redirections : > < >> <<** 

```sh
./minishell -c "whereis ls | cat -e | cat -e > test"
./minishell -c "whereis grep >> tmp/file"
./minishell
grep abcd << hello
> que
> abcdabcd 
> ab
> hello
abcdabcd
```

**Semicolons** 

```sh
./minishell -c "echo hello world ; echo this is cool"
./minishell -c "echo test | cat -e | cat -e | cat -e ; echo Abstract Sytax tree"
./minishell -c "echo this is written inside file > abc.txt; cat abc.txt"
```

## Built ins and their Test Cases 


Usually single quotes, double quotes and dollar sign are special characters that can cause expansion of variables.
Hence we needed to be thorough that our parsing is capable to handling a random mix of these special characters.
Following are the test cases of all the built-in functions we wrote.
**To test yourself, use TEST CASES, simultaneously with bash and minishell in two terminal windows**

**Echo command**
```sh
./minishell -c "echo hello world"
./minishell 
echo abcd > a.txt
```
<details><summary> Test Cases </summary>

  
```sh
./minishell
1: echo
2: echo echo
3: eCho
4: eChO
5: eCHO
6: ECHO
7: echo rhobebou
8: echo stop barking
9: echo "bonjour"
10: echo bonjour
11: echo 'bonjour'
12: echo -n bonjour
13: echo -nn bonjour
14: echo -n -n -n bonjour
15: echo -n -n -n bonjour
16: echo "-n" bonjour
17: echo -n"-n" bonjour
18: echo "-nnnn" bonjour
19: echo "-n -n -n"-n bonjour
20: echo "-n '-n'" bonjour
21: echo $USER
22: echo "$USER"
23: echo "'$USER'"
24: echo " '$USER' "
25: echo text"$USER"
26: echo text"'$USER'" ' $USER '
27: echo "text"   "$USER"    "$USER"
28: echo '              $USER          '
29: echo               text "$USER"            "$USER"text
30: echo ''''''''''$USER''''''''''
31: echo """"""""$USER""""""""
32: echo $USER'$USER'text oui oui     oui  oui $USER oui      $USER ''
33: echo $USER '' $USER $USER '' $USER '' $USER -n $USER
34: echo ' ' ' '
35: echo '" ' " """
36: echo " " " """ ''
37: echo "$USER""$USER""$USER"
38: echo text"$USER"test
39: echo '$USER' "$USER" "text ' text"
40: echo '$USER'
41: echo $USER " "
42: echo "$USER""Users/$USER/file""'$USER'"'$USER'
43: echo "$USER$USER$USER"
44: echo '$USER'"$USER"'$USER'
45: echo '"$USER"''$USER'"""$USER"
46: echo " $USER  "'$PWD'
47: echo " $USER  $ "'$PWD'
48: echo $USER=4
49: echo $USER=thallard
50: echo $USER
51: echo $?
52: echo $USER213
53: echo $USER$12USER$USER=4$USER12
54: echo $USER $123456789USER $USER123456789
55: echo $USER $9999USER $8888USER $7777USER
56: echo $USER $USER9999 $USER8888 $USER7777
57: echo $USER $USER9999 $USER8888 $USER7777 "$USER"
58: echo "$USER=12$USER"
59: echo "$9USER" "'$USER=12$SOMETHING'"
60: echo $PWD/file
61: echo "$PWD/file"
62: echo "text" "text$USER" ... "$USER"
63: echo $PWD
```

</details>

**Cd command**
```sh
./minishell -c "cd .."
./minishell 
cd /Users/
```
<details><summary> Test Cases </summary>

```sh
./minishell
1: cd
2: cd ..
3: cd .
4: cd /Users
5: cd //
6: cd '//'
7: cd //////
8: cd ./././
9: cd /
10: cd '/////' 2>/dev/null
11: cd '/etc'
12: cd '/var'
13: cd "$PWD/file_tests"
14: cd "doesntexist"
15: cd "doesntexist" 2>/dev/null
16: cd ../../..
17: cd "wtf" 2>/dev/null
18: cd ..
19: cd ..
20: cd ?
21: cd +
22: cd _
23: cd woof
24: cd bark bark
25: cd '/'
26: cd $PWD/file_tests
27: cd $OLDPWD/something
```
</details>

**Exit command**
```sh
./minishell -c "exit 42"
./minishell 
exit
```
<details><summary> Test Cases </summary>

```sh
./minishell
1: exit 0 0
2: exit 42 42
3: exit -42 -24
4: exit 42
5: exit 42 53 68
6: exit 259
7: exit -12030
8: exit --1239312
9: exit ++++1203020103
10: exit +0
11: exit ++++++0
12: exit -----0
13: exit azerty
14: exit kewkwqke
15: exit a
16: exit z
17: exit "1"
18: exit "2"
19: exit "+102"
20: exit "1230"
21: exit "+++1230"
22: exit "1"23
23: exit "2"32"32"
24: exit "'42'"
25: exit '42'"42"42
26: exit +'42'"42"42
27: exit -'42'"42"42
28: exit 9223372036854775807
29: exit 9223372036854775808
30: exit -4
31: exit wrong
32: exit wrong_command
33: exit something
34: exit 1
35: exit -1
36: exit 42
37: exit 0
38: exit --000
39: exit +++++++000
40: exit ++++3193912939
41: exit ---31232103012
42: exit "something"
43: exit q
44: exit help
45: exit export
46: exit echo
47: exit cd ..
48: exit 0 0
49: exit something somethingv2
50: exit 42 42 42 42 42
51: exit echo something
52: exit exit
```
</details>
  
**Export command**
```sh
./minishell -c "export TEST=123"
./minishell 
export TEST-=100
```
<details><summary> Test Cases </summary>

```sh
./minishell
1: export | grep "SHLVL"
2: export | grep "OLDPWD"
3: export | grep "PWD"
4: export $?
6: export TEST
7: export TEST=
8: export TEST=123
9: export ___TEST=123
10: export --TEST=123
11: export ""=""
12: export ''=''
13: export "="="="
14: export '='='='
15: export TE\ST=100
16: export TE-ST=100
17: export -TEST=100
18: export TEST-=100
19: export _TEST=100
20: export | grep "SHLVL"
21: export TEST
22: export ==========
23: export 1TEST=
24: export TEST
25: export ""=""
26: export TES=T=""
27: export TE+S=T=""
28: export TES\T=123
29: export TES.T=123  
30: export TES\$T=123
31: export TES\T
32: export TES.T=123
33: export TES+T=123
34: export TES=T=123
35: export TES}T=123
36: export TES{T=123
37: export TES-T=123
38: export -TEST=123
39: export _TEST=123
40: export TES_T=123
41: export TEST_=123
42: export TE*ST=123
43: export TES#T=123
44: export TES@T=123
45: export TES!T=123
46: export TES$?T=123
47: export =============123
48: export +++++++=123
49: export ________=123
50: export export
51: export echo
52: export pwd
53: export cd
54: export export
55: export unset
56: export sudo
57: export TES^T=123
58: export TES!T=123
59: export TES~T+=123
60: export TEST+=100
```
</details>

**Unset command**
```sh
./minishell
unset TEST
```
<details><summary> Test Cases </summary>

```sh
./minishell
1: unset
2: export TEST=100
3: unset doesntexist
4: unset PWD
5: unset PWD
6: unset OLDPWD
7: unset PATH
8: unset PATH
9: unset PATH
10: unset TES\T
11: unset TES;T
12: unset TES.T
13: unset TES+T
14: unset TES=T
15: unset TES}T
16: unset TES{T
17: unset TES-T
18: unset -TEST
19: unset _TEST
20: unset TES_T
21: unset TEST_
22: unset TE*ST
23: unset TES#T
24: unset TES@T
25: unset TES!T
26: unset TES$?T
27: unset ============
28: unset +++++++
29: unset ________
30: unset export
31: unset echo
32: unset pwd
33: unset cd
34: unset unset
35: unset sudo
36: unset TES^T
37: unset TES!T
38: unset TES~T
```
</details>


## Bug Issues 

Have a bug? If you found a problem or idea that is not addressed yet, [please open a new issue](https://github.com/harshbanthiya/Minishell/issues/new).


## Creators

[Harsh Banthiya](https://github.com/harshbanthiya)
[Sebastien Fournier](https://github.com/Fousse24)

## Request Codebase 

This is an ongoing project for a lot of students attending 42. Therefore we have only kept the executable and not the entire codebase, if you have questions regarding implementation and want to request the entire codebase. [Please write to me.](mailto:banthiyaharsh01@gmail.com?subject=[GitHub]%20Request%20Codebase%20Minishell%20Or%20Implementation)


:metal:
