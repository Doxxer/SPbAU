#!/bin/bash

# 2. Вычислить N-е число Фибоначчи рекурсивно. N передается параметром.
# Сначала проверяем, что у нас есть хоть какой-то параметр и что число больше нуля. Остальное достаточно очевидно.
# Работает правда очень медленно.

fib() {
	 n=$1
	 if [ $n -le 2 ]
	 then
		  if [ $n -eq 1 ];then echo 0;else echo 1;fi
	 else
		  n1=$((n-1))
		  n2=$((n-2))
		  f1=$(fib $n1);
		  f2=$(fib $n2);
		  f=$((f1+f2));
		  echo $f
	 fi
}


if [[ $# -gt 0 && $1 -gt 0 ]]
then
	 fib $1
else
	 echo error
fi

# После инлайна некоторых переменных и сокращения записи:

fib() {
	 n=$1
	 if [ $n -le 2 ]; then
		  if [ $n -eq 1 ]; then echo 0;else echo 1; fi
	 else echo $(($(fib $((n-1)))+$(fib $((n-2))))); fi
}

if [[ $# -gt 0 && $1 -gt 0 ]]; then fib $1; else echo error; fi