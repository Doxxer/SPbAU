# coding=utf-8

def sieve(n):
    composites = set()
    primes = []
    for i in range(2, n):
        if i not in composites:
            primes.append(i)
            composites.update(range(i*i, n, i))
    return primes

N = 105000
primes = sieve(N)
print(primes[10000])