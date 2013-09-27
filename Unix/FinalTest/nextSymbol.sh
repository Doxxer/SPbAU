#!/bin/bash

next()
{
	code=$(printf '%d' "'$1")
	nextCode=$(($code+1))
	echo $(printf \\$(printf '%03o' $nextCode))
}

string=$1
for (( i=0; i<${#string}; i++ )); do
	c=${string:$i:1}
	if [[ "$c" =~ [A-Za-z0-9_\'\.,-] ]]; then
		printf "%c" $(next $c)
	else
		printf " "
	fi
done
printf "\n"
