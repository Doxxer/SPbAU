# python3.3
# long arithmetic

def to_str(a):
    """
    Преобразовывает список цифр в число, разворачивая его
    @param a: Развернутый список цифр
    @return: Число в виде строки
    """
    s = "".join([str(x) for x in a[::-1]])
    return norm(s)


def norm(s):
    s = s.lstrip("0")
    return "0" if len(s) == 0 else s


def align_lists(a, b):
    """
    Выравнивает числа, добавляя в конец нули
    @param a: Первое число в виде строки
    @param b: Второй число в виде строки
    @return: Три значения: два списка одинаковой длины и длина списка
    """

    def to_list(s):
        """
        Преобразовывает число в виде строки в инвертированный список цифр
        @param s: Число в виде строки
        @return: Развернутый список цифр
        """
        return [int(x) for x in s[::-1]]

    a, b = to_list(norm(a)), to_list(norm(b))
    while len(a) < len(b):
        a.append(0)
    while len(b) < len(a):
        b.append(0)
    return a, b, len(a)


def is_greater(a, b):
    """
    Проверяет a > b
    @param a: Первое число в виде строки
    @param b: Второе число в виде строки
    @return: a > b ?
    """
    a, b = norm(a), norm(b)
    if len(a) != len(b):
        return len(a) > len(b)
    a, b, size = align_lists(a, b)

    for i in reversed(range(0, size)):
        if a[i] > b[i]:
            return True
    return False


def is_equal(a, b):
    """
    Проверяет a == b
    @param a: Первое число в виде строки
    @param b: Второе число в виде строки
    @return: a == b ?
    """
    if len(a) != len(b):
        return False
    a, b, size = align_lists(a, b)

    for i in range(0, size):
        if a[i] != b[i]:
            return False
    return True


def is_greater_or_equal(a, b):
    """
    Проверяет a>== b
    @param a: Первое число в виде строки
    @param b: Второе число в виде строки
    @return: a >= b ?
    """
    return is_greater(a, b) | is_equal(a, b)


def is_less_or_equal(a, b):
    """
    Проверяет a <= b
    @param a: Первое число в виде строки
    @param b: Второе число в виде строки
    @return: a <= b ?
    """
    return not is_greater(a, b)


def is_less(a, b):
    """
    Проверяет a < b
    @param a: Первое число в виде строки
    @param b: Второе число в виде строки
    @return: a < b ?
    """
    return is_less_or_equal(a, b) & (not is_equal(a, b))


def long_add(a, b):
    """
    Длинное сложение
    @param a: Первое число в виде строки
    @param b: Второе число в виде строки
    @return:
    """
    a, b, size = align_lists(a, b)
    carry = 0
    for i in range(0, size):
        a[i] += carry + b[i]
        carry = a[i] >= 10
        if carry:
            a[i] -= 10
    if carry:
        a.append(1)
    return to_str(a)


def long_sub(a, b):
    """
    Длинное вычитание
    @param a: Первое число в виде строки
    @param b: Второе число в виде строки
    @return: Результат a-b
    """

    def long_sub_unsigned(a, b):
        """
        Длинное вычитание only if (a >= b)
        @param a: Первое число в виде строки
        @param b: Второе число в виде строки
        @return: Результат a-b
        """
        a, b, size = align_lists(a, b)
        carry = 0
        for i in range(0, size):
            a[i] -= carry + b[i]
            carry = a[i] < 0
            if carry:
                a[i] += 10
        if carry:
            a.append(1)
        return to_str(a)

    if is_greater_or_equal(a, b):
        return long_sub_unsigned(a, b)
    return "-" + long_sub_unsigned(b, a)


def long_mul(a, n):
    """
    Умножение длинного на короткое
    @param a: Длинное число в виде строки
    @param n: Короткое число в виде числа
    @return: Результат умножения в виде строки
    """
    a, t, size = align_lists(a, "")
    carry = 0
    for i in range(0, size):
        c = carry + a[i] * n
        a[i] = c % 10
        carry = c // 10
    if carry > 0:
        a.extend([int(x) for x in str(carry)[::-1]])
    return to_str(a)

x = "0"
y = "2151234"
n = 123

print("%s + %s = %s" % (x, y, long_add(x, y)))
print("%s - %s = %s" % (x, y, long_sub(x, y)))
print("%s > %s = %s" % (x, y, is_greater(x, y)))
print("%s == %s = %s" % (x, y, is_equal(x, y)))
print("%s >= %s = %s" % (x, y, is_greater_or_equal(x, y)))
print("%s <= %s = %s" % (x, y, is_less_or_equal(x, y)))
print("%s < %s = %s" % (x, y, is_less(x, y)))
print("%s * %s = %s" % (x, n, long_mul(x, n)))