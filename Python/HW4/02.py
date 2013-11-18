#!/usr/bin/python
# coding=utf-8

# Напишите скрипт, который принимает на вход имя файла написанного на Python
# после чего декорирует каждый метод в этом файле таким образом,
# чтобы при запуске любого метода выдавалась информация о времени работы функции:

import time
import sys
global_begin = time.time()


def timer(func):
    def wrapper(*args, **kwargs):
        time_from_begin = time.time() - global_begin
        time_before = time.time()
        res = func(*args, **kwargs)
        print("{0:3.3f}ms {1}\n\t+{2:3.3f}ms".format(time_from_begin, func.__name__, time.time() - time_before))
        return res

    return wrapper


if __name__ == '__main__':
    file_name = sys.argv[1] if len(sys.argv) > 1 else "test.py"
    script = ""
    with open(file_name, "r") as file:
        for line in file.readlines():
            assert isinstance(line, str)
            if line.strip()[:4] == "def ":
                spaces_len = len(line.split("def ")[0])
                line = "{0}@timer\n{1}".format(" " * spaces_len, line)
            script += line
    exec(script, globals())