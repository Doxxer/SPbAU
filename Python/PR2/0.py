def merge(*iters):
    iters = list(iter(i) for i in iters)
    while iters:
        for i in iters:
            try:
                yield next(i)
            except StopIteration as e:
                iters.remove(i)


q = merge([1, 2, 3, 5], [4, 5])
print(list(q))
