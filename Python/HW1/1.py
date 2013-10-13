# coding=utf-8
# Найти все составные числа, меньшие N, которые представимы в виде произведения двух простых чисел


def sieve(n):
    composites = set()
    result = []
    for i in range(2, n):
        if i not in composites:
            result.append(i)
            composites.update(range(i * i, n, i))
    return result


N = int(input("Input N: "))
#    N = 10000
primes = sieve(N)
result = list(set([i * j for i in primes for j in primes if i * j < N]))
result.sort()
print(result)