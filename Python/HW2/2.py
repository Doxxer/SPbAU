#coding: utf-8
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
    """
    Очищает число от ведущих нулей
    @param s: число в виде строки
    @return: Очищенное число
    """
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
    return not is_less(a, b)


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
    return is_greater(b, a)


def long_add(a, b):
    """
    Длинное сложение
    @param a: Первое число в виде строки
    @param b: Второе число в виде строки
    @return: a+b в виде строки
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


def long_mul(a, b):
    """
    Умножение длинного на короткое
    @param a: Длинное число в виде строки
    @param b: Короткое число в виде числа
    @return: Результат умножения в виде строки
    """

    def long_mul_short(x, n):
        """
        Умножение длинного на короткое
        @param x: Длинное число в виде строки
        @param n: Короткое число в виде числа
        @return: Результат умножения в виде строки
        """
        x, t, size = align_lists(x, "")
        carry = 0
        for i in range(0, size):
            c = carry + x[i] * n
            x[i] = c % 10
            carry = c // 10
        if carry > 0:
            x.extend([int(k) for k in str(carry)[::-1]])
        return to_str(x)

    if len(a) < len(b):
        a, b = b, a

    c = "0"
    mem = {}
    for i, digit in enumerate(b[::-1]):
        digit = int(digit)
        if digit not in mem:
            mem[digit] = long_mul_short(a, digit)
        c = long_add(c, (mem[digit] + "0" * i))
    return c


def long_pow(a, b):
    """
    Возведение длинного числа в длинную степень
    @param a: Длинное число в виде строки
    @param b: Длинный показатель степени в виде строки
    @return: Результат a ** b в виде строки
    """
    res, cur, n = "1", a, int(b)
    while n > 0:
        if n % 2:
            res = long_mul(res, cur)
        cur = long_mul(cur, cur)
        n //= 2
    return res


def long_div_short(a, n):
    if (is_less(a, str(n))):
        return "0", a
    a, t, size = align_lists(a, "")
    carry = 0
    for i in reversed(range(0, len(a))):
        cur = a[i] + carry * 10
        a[i] = cur // n
        carry = cur % n
    return to_str(a), carry


x = "100000000"
y = "3"
n = 463

print("%s + %s = %s\n\t%r" % (x, y, long_add(x, y), int(long_add(x, y)) == int(x) + int(y)))
print("%s - %s = %s\n\t%r" % (x, y, long_sub(x, y), int(long_sub(x, y)) == int(x) - int(y)))
print("%s > %s = %s\n\t%r" % (x, y, is_greater(x, y), int(is_greater(x, y)) == (int(x) > int(y))))
print("%s == %s = %s\n\t%r" % (x, y, is_equal(x, y), int(is_equal(x, y)) == (int(x) == int(y))))
print("%s >= %s = %s\n\t%r" % (x, y, is_greater_or_equal(x, y), int(is_greater_or_equal(x, y)) == (int(x) >= int(y))))
print("%s <= %s = %s\n\t%r" % (x, y, is_less_or_equal(x, y), int(is_less_or_equal(x, y)) == (int(x) <= int(y))))
print("%s < %s = %s\n\t%r" % (x, y, is_less(x, y), int(is_less(x, y)) == (int(x) < int(y))))
print("%s * %s = %s\n\t%r" % (x, y, long_mul(x, y), int(long_mul(x, y)) == (int(x) * int(y))))
print("%s ** %s = %s\n\t%r" % (x, y, long_pow(x, y), int(long_pow(x, y)) == (int(x) ** int(y)) ))

q, w = long_div_short(x, n)
print("%s / %s = %s (%s)\n\t%r, %r" % (x, n, q, w, int(x) // n == int(q), int(x) % n == int(w)))