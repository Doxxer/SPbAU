#!/bin/bash
# Написать скрипт, который принимает на вход 2 числа (n, m). После чего создает N каталогов (с названиями input1, input2...) в каждом из которых создает файл input.txt состоящий из m случайных чисел.

read n
read m
inp="input"

for i in $( seq $n )
do
mkdir inp$i
cd inp$i
touch input.txt
	for j in $( seq $m )
	do
		echo $RANDOM" " >> input.txt	
	done
cd ..
done