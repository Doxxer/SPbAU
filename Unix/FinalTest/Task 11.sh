#!/bin/bash
# Написать скрипт, который принимает в качестве параметров день, месяц и год и должен выдать на экран какой это день недели. Решать задачу можно только через обработку результатов команды сal.

yyyy=$1
mm=$2
dd=$3

date="$yyyy-$mm-$dd"

pos=$(cal -H $date | grep -E "_.._" -bo | sed 's/:.*$//')
let pos=$pos%23
#echo $pos

week=$(cal -H $date | head -n 2 | tail -n 1)
# echo $week

day=$(echo $week | sed -r -e "s/..{$pos}(..).*/\1/");
echo $day
