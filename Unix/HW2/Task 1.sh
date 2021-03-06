#/bin/bash

# 1. Посчитать число юзеров в группе.

# Есть проблема: в файле /etc/group у группы написаны не все пользователи - там нет юзеров, у которых эта группа выставлена как основная в файле /etc/passwd. Поэтому просто грепнуть /etc/group было бы неправильно. Нужно смотреть и туда, и туда.
# Возникает еще одна проблема - группа у пользователя в /etc/passwd записана в виде числа.
#Поэтому алгоритм такой: 


#	* Возьмем группу из /etc/group, выцепим из нее всех пользователей, а также запомним номер этой группы

#	* Посмотрим на файл /etc/passwd и найдем всех пользователей, у которых эта группа проставлена в качестве основной
#	* Суммарное число пользователей и будет ответом.

if [[ $# -ne 1 ]]; then echo "Usage: $ bash $0 'group name'"; exit; fi # небольшая проверка на ошибки в самом начале


group=$(grep ^"$1": /etc/group) # ищем нашу группу в файле всех групп

if ! [ $group ]; then echo "There's no group '$1'"; exit; fi # если группа не найдена, то пишем ошибку и выходим



groupID=$(echo $group | cut -d: -f3) # делим запись группы по разделителям "двоеточие" и берем третью запись - это код группы


usersInGroup=$(echo $group | cut -d: -f4 | sed 's/,/ /g') # а четвертая запись с удаленными запятыми - пользователи в группе
numUsersInGroup=$(echo $usersInGroup | wc -w) # считаем число пользователей


usersInPasswd=$(echo $(cat /etc/passwd | cut -d: -f1,4 | grep :"$groupID"$ | cut -d: -f1)) # смотрим файл /etc/passwd, вырезаем из каждой строчки первую (это имя юзера) и четвертую (это код его основной группы) запись, грепаем по коду, вырезаем первую запись - получаем имя юзера
numUsersInPasswd=$(echo $usersInPasswd | wc -w) # считаем число юзеров
sum=$(expr $numUsersInGroup + $numUsersInPasswd) # считаем сумму


# ----------------- Вывод ---------------------
# просто красивый вывод, ответ уже фактически находится в переменной sum
echo "GroupName = $1"
echo "GroupID = $groupID"
echo "Users in /etc/group (#$numUsersInGroup): $usersInGroup"
echo "Users in /etc/passwd (#$numUsersInPasswd): $usersInPasswd"


echo "Sum = $sum"

Второе решение, забавное: members $1 | wc -w
(перед этим надо бы сделать sudo apt-get install members) - вот members делает как раз то, что описано в первом решении.