class UML(type):
    __root = None
    __hierarchy = {}
    __instances = {}


    def __init__(cls, name, bases, dct):
        super(UML, cls).__init__(name, bases, dct)
        if not cls.__root:
            cls.__root = cls
        for base in bases:
            if base in cls.__hierarchy:
                cls.__hierarchy[base].append(cls)
        cls.__hierarchy[cls] = []
        cls.__instances[cls] = 0

    def __call__(cls, *args, **kwargs):
        cls.__instances[cls] += 1
        return super(UML, cls).__call__(*args, **kwargs)

    @staticmethod
    def drawUML(cls):
        def print_children(some_class, indent):
            for child in some_class.__hierarchy[some_class]:
                print(indent + child.__name__ + ": " + str(child.__instances[child]))
                print_children(child, indent + '\t')

        if not cls.__root is cls:
            print("Error: class must have metaclass UML")
            return
        print(cls.__name__ + ": " + str(cls.__instances[cls]))
        print_children(cls, '\t')


class A(object, metaclass=UML):
    pass


class B(A):
    pass


class C(B):
    pass


class D(B):
    pass


class E(A):
    pass


class F(A):
    pass


class AA(object):
    pass


class BB(AA, metaclass=UML):
    pass


class CC(BB):
    pass


A()
A()
A()
A()
B()
B()
B()
B()
B()
B()
C()
C()
C()
C()
C()
C()
C()
C()
D()
F()
F()

UML.drawUML(A)