# coding=utf-8
# Функция, вычисляющая произведение двух матриц

from numpy import dot

def matrix_multiplication(a, b):
    rows_a = len(a)
    cols_a = len(a[0])
    rows_b = len(b)
    cols_b = len(b[0])

    if cols_a != rows_b:
        print("error")
        return

    c = [[0 for row in range(cols_b)] for col in range(rows_a)]
    for i in range(rows_a):
        for j in range(cols_b):
            for k in range(cols_a):
                c[i][j] += a[i][k] * b[k][j]
    return c

def numpy_matrix_multiplication(a, b):
    return dot(a, b)

#x = [[1,2,3],[4,5,6],[7,8,9],[10,11,12]]
# y = [[1,2],[1,2],[3,4]]

x = input("input x: ")
y = input("input y: ")

print(matrix_multiplication(x, y))
print(numpy_matrix_multiplication(x, y))
