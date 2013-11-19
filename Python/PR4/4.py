import datetime

G = {}


def spy(func):
    def wrapper(*args, **kwargs):
        result = func(*args, **kwargs)
        fname = func.__name__
        if fname not in G.keys():
            G[fname] = {}
        if 'time' not in G[fname].keys():
            G[fname]['time'] = []
        if 'args' not in G[fname].keys():
            G[fname]['args'] = []

        G[fname]['time'].append(datetime.datetime.now())
        G[fname]['args'].append(args)

        return result

    return wrapper


@spy
def foo(n):
    pass

@spy
def bar(n):
    pass

def bond(func):
    a = list(G[func]['args'])
    t = list(G[func]['time'])

    for i in range(len(a)):
        yield dict(time=t[i], args=a[i])


foo(2)
foo(4)
foo(6)

bar(10)
bar(20)

for q in bond('foo'):
    print(q['time'], q['args'])

for q in bond('bar'):
    print(q['time'], q['args'])
