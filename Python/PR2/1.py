#python3.3
#coding: utf-8


import random


def merge(i1, i2):
    i1, i2 = iter(i1), iter(i2)
    a, b = None, None
    try:
        a = next(i1)
        b = next(i2)
        while 1:
            if a <= b:
                yield a
                a = next(i1)
            else:
                yield b
                b = next(i2)
    except StopIteration:
        if a is not None and b is not None:
            yield max(a, b)
        elif a is not None:
            yield a
        else:
            yield b

        yield from i1
        yield from i2
        return


def merge_sort(it):
    res = [[x] for x in it]
    while 1:
        try:
            l1 = res.pop(0)
            l2 = res.pop(0)
            res.append(list(merge(l1, l2)))
        except IndexError:
            res.append(l1)
            yield from res[0]
            return


class random_iterator:
    def __init__(self, n):
        self.max = n
        self.current = 0

    def __iter__(self):
        return self

    def __next__(self):
        self.current += 1
        if self.current <= self.max:
            return random.randrange(0, 100)
        raise StopIteration()


a = random_iterator(20)
print(list(merge_sort(a)))