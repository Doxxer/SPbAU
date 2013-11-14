#!/usr/bin/python
# coding=utf-8

# Создайте декоратор @singleton, который будучи приписан к классу превращает его в класс Singleton


def singleton(cls):
    instances = {}

    def get_instance(*args, **kwargs):
        instances[cls] = instances.get(cls, cls(*args, **kwargs))
        return instances[cls]

    return get_instance


@singleton
class MyClass(object):
    def __init__(self, initial_value):
        self._value = initial_value

    def __repr__(self):
        return str(self._value)

    def inc(self):
        self._value += 1

    def dec(self):
        self._value -= 1


if __name__ == '__main__':
    a = MyClass(10)
    b = MyClass(10000)
    a.inc()
    a.inc()
    print(a) # 12
    b.dec()
    print(b) # 11, not 9999! cuz it's a singleton