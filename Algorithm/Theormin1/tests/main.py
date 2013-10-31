import random
import subprocess

N = 1000
MAX = 10000
TESTS = 10000
PATH_INPUT = "input.txt"
PATH_OUTPUT = "output.txt"
PATH_OUTPUT_right = "right.txt"
COMMAND = "/Users/doxer/Documents/GitRepositories/SPbAU/Algorithm/Theormin1/main.out"
COMMAND_RIGHT = "./main1.out"


def generateInput():
    c = random.randint(N// 2, N)
    q = random.sample(range(MAX + 1), c)
    with open(PATH_INPUT, 'w') as f:
        print(str(c), file=f)
        print(" ".join(str(x) for x in q), file=f)
        print(random.randint(1, c), file=f)


def run():
    process = subprocess.Popen(COMMAND)
    process.wait()


def check():
    process = subprocess.Popen(COMMAND_RIGHT)
    process.wait()

    with open(PATH_OUTPUT, 'r') as myf:
        a1, a2 = myf.readline(), myf.readline()
    with open(PATH_OUTPUT_right, 'r') as rf:
        r1, r2 = rf.readline(), rf.readline()

    a1, a2 = sorted(a1.split()), sorted(a2.split())
    r1, r2 = sorted(r1.split()), sorted(r2.split())

    return a1 == r1 and a2 == r2


for test in range(1, TESTS + 1):

    generateInput()
    run()
    if not check():
        if test % 100 == 0: print("test %d ... failed" % test)
        break
    else:
        if test % 100 == 0: print("test %d ... ok" % test)