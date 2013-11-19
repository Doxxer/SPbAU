# coding=utf-8

def diff(a, b):
    """
    Levenstein distance (писал этот метод когда решал Розалинд)
    @param a: word1
    @param b: word2
    @return: distance
    """
    if not a: return len(b)
    if not b: return len(a)

    diff1 = diff(a[1:], b[1:]) + (a[0] != b[0]) # change
    diff2 = diff(a[1:], b) + 1 # insert
    diff3 = diff(a, b[1:]) + 1 # insert
    return min(diff1, diff2, diff3)


def graph(abc):
    dict = {}
    for v in abc:
        for word in abc:
            if diff(v, word) == 1:
                if v not in dict.keys():
                    dict[v] = []
                dict[v].append(word)
    return dict


def BFS(graph, root, target):
    q = [root]
    checked = [root]
    par = {}
    while q:
        v = q.pop(0)
        if v == target:
            return par
        else:
            if v in graph.keys():
                for to in graph[v]:
                    if to not in checked:
                        checked.append(to)
                        q.append(to)
                        par[to] = v
    return None


def solve(abc, begin, end):
    abc.append(begin)
    abc.append(end)

    result = BFS(graph(abc), begin, end)

    if not result:
        print("IMPOSSIBRU!!!")
    else:
        solution = [end]
        while end != begin:
            solution.append(result[end])
            end = result[end]

        for word in solution[::-1]:
            print(word)


if __name__ == "__main__":
    abc = ["МАК", "МАГ", "МАЙ", "ЧАЙ", "ПОТ", "ЧАН", "ЧАЙ"]
    begin = "МИГ"
    end = "ЧАС"

    solve(abc, begin, end)

    abc2 = ["ДЕТИ"]
    solve(abc2, begin, end)