#!/usr/bin/python
# python3.3
# coding=utf-8

# Реализовать декоратор @abstract и метакласс Abstract - запрещающие
# создавать инстансы абстракных классов. Класс считается абстрактным, если в
# нем есть методы отмеченные как @abstract, или среди его непосредственных
# базовых классов есть класс, абстрактные методы которого не переопределены.


class Abstract(type):
    def __call__(cls, *args, **kwargs):
        if cls.is_abstract():
            raise TypeError("Can't create instance of \"{0}\". Class \"{0}\" is abstract".format(cls.__name__))

        return type.__call__(cls, *args, **kwargs)

    def is_abstract(cls):
        if any(decorator == "__abstract__function__" for decorator in cls.__dict__.values()):
            return True

        if any(value == "__abstract__function__" and key not in cls.__dict__
               for base_class in cls.__bases__
               for key, value in base_class.__dict__.items()):
            return True

        return False


def abstract(func):
    return "__abstract__function__"


class Interface(object, metaclass=Abstract):
    @abstract
    def foo(self, param1, param2=None):
        pass


class StillAbstractDerivedClass(Interface):
    pass


class Implementation(Interface):
    def foo(self, param1, param2=None):
        print("It's ok! Num={0}, q = {1}".format(param1, param2))


if __name__ == "__main__":
    # i = Interface() # TypeError
    # c = StillAbstractDerivedClass()  # TypeError, no override foo
    ok = Implementation()
    ok.foo(42, 1777)