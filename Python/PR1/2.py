from fractions import gcd
from functools import reduce


def lcm(a, b):
    return a * b // gcd(a, b)


def lcm2(numbers):
    return reduce(lcm, numbers)

N = 5
print(lcm2(range(1, N + 1)))
