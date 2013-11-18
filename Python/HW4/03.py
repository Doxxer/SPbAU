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

        return super(Abstract, cls).__call__(*args, **kwargs)

    def is_abstract(cls):
        cls_is_abstract = False
        for func in cls.__dict__.values():
            if hasattr(func, "__abstract_function"):
                print("Class \"{0}\" has an abstract method \"{1}\"!".format(cls.__name__, func.__name__))
                cls_is_abstract = True

        def check_parents(some_class):
            parent_has_abstract_method = False
            for base in some_class.__bases__:
                for key, func in base.__dict__.items():
                    if hasattr(func, "__abstract_function") and (
                            not key in cls.__dict__ or hasattr(cls.__dict__[key], "__abstract_function")):
                        print(
                            "Error: In class \"{0}\" an abstract method \"{1}\" from parent class \"{2}\" isn't implemented!".format(
                                cls.__name__, func.__name__, base.__name__))
                        parent_has_abstract_method = True
                parent_has_abstract_method |= check_parents(base)
            return parent_has_abstract_method

        cls_is_abstract |= check_parents(cls)
        return cls_is_abstract


def abstract(func):
    func.__abstract_function = True
    return func


class Interface(object, metaclass=Abstract):
    @abstract
    def foo(self, param1, param2=None):
        pass


class StillAbstractDerivedClass(Interface):
    pass


class TwiceStillAbstractDerivedClass(StillAbstractDerivedClass):
    pass


class Implementation(Interface):
    def foo(self, param1, param2=None):
        print("It's ok! Num = {0}, q = {1}".format(param1, param2))


if __name__ == "__main__":
    #i = Interface() # TypeError
    #c = StillAbstractDerivedClass()  # TypeError, no override foo
    #q = TwiceStillAbstractDerivedClass()
    ok = Implementation()
    ok.foo(42, 1777)