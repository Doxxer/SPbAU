#!/bin/bash
# Есть файл цитат вида (в первой строке – автор, во второй – количество цитат)
# Требуется написать скрипт, выбирающий из подобного файла случайную цитату и выводящий ее на экран

# filename
FILE="quote.txt"

author=$(head -n 1 $FILE)
#echo $author

# quote number
let num=$(head -n 2 $FILE | tail -n 1)-1
#echo $num

n=$(shuf -i 0-$num -n 1)
st_line="* $n";

flag=false
cat quote.txt | \
while read line; do  
  if [[ $line == $st_line ]]; then    
    flag=true
  else
    if [[ $(echo "$line" | grep -E "\* [0-9]+") > 0 ]]; then
      flag=false
    else
      if [[ $flag == true ]]; then
	echo "$line"
      fi
    fi
  fi  
done

echo "($author)"

