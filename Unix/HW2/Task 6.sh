#!/bin/bash

# 6. Вывести содержимое архивов.

if [ $# -eq 0 ]; then echo "Usage: $ bash $0 'params archives'";exit;fi

for file in $*; do
     if ! [ -e "$file" ]; then echo "File '$file' doesn't exist!";
     else
          if [ $(echo "$file" | grep -E '(\.gz$)|(\.bz2$)|(\.tar$)|(zip$)') ] # проверяем, что это действительно архив
          then
               echo "################################### Content of $file:"
               if [ $(echo "$file" | grep -E '\.zip$') ] # если это zip-архив, то запускаем unzip -l, иначе tar -tvf (можно без -v)
               then              
                    unzip -l "$file"
               else
                    tar -tf $file
               fi
               echo "################################### End of content of $file"
          else
               echo "File '$file' is in incorrect format"               
          fi         
     fi
done