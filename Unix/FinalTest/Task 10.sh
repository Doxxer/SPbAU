#!/bin/bash
# Написать bash скрипт, определяющий является ли строка, переданная в качестве параметра, палиндромом (читается одинаково в обе стороны)

rev=$(echo "$1" | rev)

if [ "$rev" = "$1" ]; then
	echo \""$1"\" is palindrome
else
	echo \""$1"\" is not palindrome
fi
