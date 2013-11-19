class ClassBase(type):
    def __init__(cls, name, bases, dict):
        super(ClassBase, cls).__init__(name, bases, dict)
        filename = "{0}.txt".format(cls.__name__)
        try:
            with open(filename) as file:
                for line in file.readlines():
                    field, value = line.strip().split(":")
                    setattr(cls, field.strip(), value.strip())
        except FileNotFoundError as ex:
            print("File \"{0}\" not found!".format(filename))
            raise ex


class A(object, metaclass=ClassBase):
    pass


#class B(object, metaclass=ClassBase): # error!
#    pass


a = A()
print(a.x, a.y, a.z)