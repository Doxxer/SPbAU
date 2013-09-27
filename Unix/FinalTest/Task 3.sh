#!/bin/bash
# Task3
# Напишите скрипт, который рекурсивно обходит каталог (переданный в качестве параметра) и выводит имена всех файлов, хозяином которых является текущий пользователь, и возраст которых больше N (второй параметр) дней. Если параметры не переданы, должна быть выдана ошибка.


function f()
{
	for file in "$1"/*
	do
		if [[ -e "$file" ]]; then
			if [[ -d "$file" ]]; then f "$file";
			else			
				owner=$(stat -c %U "$file")
				if [[ owner=$USER ]]; then
					current=$(date +%s)
					update=$(stat -c %Y "$file")
					((dist = current - update ))
					((dist = dist /(60*60*24) ))
				  if [[ dist -ge 10 ]]; then 
					  echo "$file" ----- $dist
				  fi
				fi
			fi
		fi
	done
}

f $1