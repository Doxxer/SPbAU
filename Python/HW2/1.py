#python3.3
#coding: utf-8
# Греческий алфавит

def GreekLowercaseAlphabet():
    for i in range(945, 970):
        if i not in [962]:
            print(chr(i), end=' ')
    print()


def GreekCapitalAlphabet():
    for i in range(913, 938):
        if i not in [930]:
            print(chr(i), end=' ')
    print()

GreekCapitalAlphabet()
GreekLowercaseAlphabet()