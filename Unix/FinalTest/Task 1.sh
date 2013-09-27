#!/bin/bash
# Напишите скрипт, рисующий шахматную доску в консоли.

clear
echo " a b c d e f g h"
for (( i=1 ; i<=8 ; i++ ))
do
  echo -e -n "\033[0m"$i
  for (( j=1 ; j<=8 ; j++ ))
  do
    if [ $(expr $(($i+$j)) % 2) -eq 1 ]
    then
        echo -e -n "\033[47m  "
    else
        echo -e -n "\033[40m  "
    fi
  done  
  echo
done

echo -e "\033[0m"
