#!/bin/bash
# 1. Напишите Bash-скрипт, который получает из Интернета страничку нашего курса с Вики и выводит список дат, в которые были лекции.
# Указание. Может помочь утилита wget.

wget -q -O - "http://mit.spbau.ru/sewiki/index.php/Unix_и_Скриптовые_языки_2013" | grep -oE "[0123][0-9]\.[01][0-9]\.2013"