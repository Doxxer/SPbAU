#/bin/bash
# 4. Написать приветствие в консоли

# 1.sh
echo
if [ $(id -u) -eq 0 ]
then
     echo "Не сиди под рутом!"
else
     echo "Hi, $(whoami)!"
fi

if [ $SHELL = "/bin/bash" ]
then
     echo "You're using bash"
else
     echo "What the hell are you using? Oh, it's $SHELL!"
fi

Затем сказать
sudo cp 1.sh /etc/profile.d
# Проверялось в Ubuntu 12.04 (в консоли по Ctrl+Alt+F1-F6)