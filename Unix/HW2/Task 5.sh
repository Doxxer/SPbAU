#!/bin/bash

# 5. Вывести n случайных паролей длины m.
if [ $# -ne 2 ]; then echo "Usage: $ bash $0 n m";exit;fi

for i in $(seq $1); do
     echo $(tr -cd [:alnum:] < /dev/urandom | head -c$2) # вырезаем только буквы и цифры
done