def ok(n):
    if n == 1:
        return 0
    temp = n
    while n % 3 == 0:
        n //= 3
    while n % 5 == 0:
        n //= 5
    return temp if n == 1 else 0


N = 16
print(sum(map(ok, range(1, N))))
