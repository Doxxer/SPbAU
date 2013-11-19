import sys


def lex(list):
    """
    Ядро задачи.
    Генерация всех перестановок списка
    @param list:
    """
    if not len(list):
        yield []
    for index, value in enumerate(list):
        for perm in lex(list[:index] + list[index + 1:]):
            yield [value] + perm


def lex_list(n):
    """
    Генерирует все перестановки списка от 1 до n
    @param n: число элементов в списке
    """
    yield from lex([x + 1 for x in range(n)])


if __name__ == "__main__":
    # task 1
    for perm in lex_list(3):
        print(perm)

    print()

    # task 2
    my_list = [7, 2, 6]
    for perm in lex(my_list):
        print(perm)

    print()

    # task 3
    my_list_param = sys.argv[1:]
    if len(my_list_param):
        for perm in lex(my_list_param):
            print(perm)