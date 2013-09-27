#!/bin/bash
# Проверьте, что для всех файлов с расширением .c в текущем каталоге в этом же каталоге есть все подключаемые ими файлы .h

for file in *.c; do
	echo "parsing $file..."  
	for include in $(grep '^#include' "$file" | sed -e 's/#include ["<]//;s/[">]//'); do
		if ! [ -e "$include" ]
		then
			echo "!!! File '$include' doesn't exist"; break;
		fi
	done
done
