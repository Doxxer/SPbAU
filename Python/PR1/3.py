def f():
    a, b = 0, 1
    while 1:
        yield a
        a, b = b, a + b


a = f()
a.next()

s = 0
for i in range(1, 100):
    n = a.next()
    # print n
    if n <= 4000000:
        if i % 2 == 0:
            s = s + n
    else:
        break

print(s)
