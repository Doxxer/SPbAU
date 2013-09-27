#!/bin/bash
# Напишите скрипт, который принимает на вход число N и выводит на экран таблицу умножения NxN

N=$1
for i in $(seq $N)
do
	for j in $(seq $N)
	do
		n=$(expr $i \* $j)
		printf '%4d' $n
	done
echo
done
