#!/bin/bash
# Напишите скрипт, который принимает на вход число N и выводит на экран таблицу умножения NxN в двоичной системе счисления

N=$1

for i in $(seq $N)
do
	for j in $(seq $N)
	do
		n=$(expr $i \* $j)
		binary=$(echo "obase=2; $n" | bc)
		printf '%10d' $binary
	done
echo
done
