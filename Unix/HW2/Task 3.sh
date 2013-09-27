#/bin/bash
# 3. Перевернуть расширение файла

# Все должно быть понятно из комментариев.
# Замечание: работает и с файлами из текущей папки и с файлами по абсолютному пути (/home/user/.…..).
# Также работает на файлах с пробелами и с точками в имени

if [[ $# -ne 1 ]]; then echo "Usage: $ bash $0 'file name'"; exit; fi # небольшая проверка на ошибки в параметрах

file=$1
if ! [ -e "$file" ]; then echo "File '$file' doesn't exist"; exit; fi # если файла нет, то сообщаем об этом и выходим

normalExtension=${file##*.} # удаляем самую длинную подстроку слева
noExtension=${file%.*}	# удаляем самую коротку подстроку справа
reverseExtension=$(echo $normalExtension | rev) # разворачиваем

mv "$file" "$noExtension.$reverseExtension" # переименовываем файл