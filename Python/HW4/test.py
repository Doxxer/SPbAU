from time import sleep


def func1():
    sleep(1)


def func15():
    sleep(1.5)


class A():
    def func0(self):
        print("Hi, I'm func0")


    def func05(self):
        sleep(0.5)


a = A()
a.func0()
a.func05()
func1()
func15()