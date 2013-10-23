#python3.3
#coding: utf-8

from itertools import groupby
from operator import itemgetter


def task1():
    N = 10
    for row in ([1 if abs(x - (N - 1) / 2) < min(y + 1, abs(N - y)) else 0
                 for x in range(N)]
                for y in range(N)):
        print(row)


def task2():
    dict = [("abc def", "SE"), ("troll face", "CS"), ("ololosh", "BI"), ("chuck norris", "SE"), ("no name", "SE"),
            ("1 2", "BI")]

    for g in (sorted(group)
              for course, group in groupby(sorted(dict, key=itemgetter(1)), itemgetter(1))):
        print(list(g))


task1()
task2()
