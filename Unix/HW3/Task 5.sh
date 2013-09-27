#/bin/bash

# 5. Вывести названия подключаемых библиотек из файла file.c
grep '^#include' file.c | sed -e 's/#include ["<]//;s/[">]//'