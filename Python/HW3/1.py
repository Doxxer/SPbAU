import math

class Vector(object):
    def __init__(self, v):
        self._data = [0, 0, 0]
        for i in range(len(v)):
            self._data[i] = v[i]

    def __repr__(self):
        return "{0}\n".format(" ".join(map(lambda x: str("%3.2f" % x), self._data)))


class Matrix(object):
    def __init__(self, m):
        self._data = [[0 for i in range(3)] for i in range(3)]
        for i in range(len(m)):
            for j in range(len(m[i])):
                self._data[i][j] = m[i][j]

    def __repr__(self):
        return "{0}\n".format("\n".join([" ".join(map(lambda x: str("%3.2f" % x), row)) for row in self._data]))

    def __add__(self, other):
        if not isinstance(other, Matrix):
            raise Exception("Adding error. Can only add matrix to matrix, not %s" % type(other))

        m1 = self._data
        m2 = other._data
        return Matrix([[m1[i][j] + m2[i][j] for j in range(3)] for i in range(3)])

    def _matrix_multiplication(self, other):
        m1 = self._data
        m2 = other._data
        r = [
            [
                sum([m1[i][k] * m2[k][j] for k in range(3)])
                for j in range(3)
            ]
            for i in range(3)]
        return Matrix(r)

    def _vector_multiplication(self, other):
        m1 = self._data
        m2 = other._data
        r = [sum([m1[i][j] * m2[j] for j in range(3)]) for i in range(3)]
        return Vector(r)

    def _number_multiplication(self, other):
        r = [[i * other for i in r] for r in self._data]
        return Matrix(r)

    def __mul__(self, other):
        if isinstance(other, Matrix):
            return self._matrix_multiplication(other)
        elif isinstance(other, Vector):
            return self._vector_multiplication(other)
        elif isinstance(other, int) or isinstance(other, float):
            return self._number_multiplication(other)
        else:
            raise Exception("Multiple error. Can't multiple matrix by type %s" % type(other))

    def __invert__(self):
        d = self._det()
        if d == 0:
            raise Exception("Error. Determinant=0")

        m = self._data
        r = [[0 for i in range(3)] for i in range(3)]
        r[0][0] =  (m[1][1] * m[2][2] - m[2][1] * m[1][2])
        r[1][0] = -(m[1][0] * m[2][2] - m[2][0] * m[1][2])
        r[2][0] =  (m[1][0] * m[2][1] - m[2][0] * m[1][1])
        r[0][1] = -(m[0][1] * m[2][2] - m[2][1] * m[0][2])
        r[1][1] =  (m[0][0] * m[2][2] - m[2][0] * m[0][2])
        r[2][1] = -(m[0][0] * m[2][1] - m[2][0] * m[0][1])
        r[0][2] =  (m[0][1] * m[1][2] - m[1][1] * m[0][2])
        r[1][2] = -(m[0][0] * m[1][2] - m[1][0] * m[0][2])
        r[2][2] =  (m[0][0] * m[1][1] - m[1][0] * m[0][1])
        return Matrix(r) * (1 / d)

    def _det(self):
        m = self._data
        return ( + m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
                 - m[0][1] * (m[1][0] * m[2][2] - m[2][0] * m[1][2])
                 + m[0][2] * (m[1][0] * m[2][1] - m[2][0] * m[1][1])
        )


class ZRotationMatrix(Matrix):
    def __init__(self, angle):
        a = (angle * math.pi) / 180.0
        m = [[math.cos(a), -math.sin(a), 0]
            , [math.sin(a), math.cos(a), 0]
            , [0, 0, 1]]
        super(ZRotationMatrix, self).__init__(m)


v = Vector([2.4, 3, 4])
print(v)

print("Multiplication test:")
m = Matrix([[2, 5, 10], [1, 2, -5], [3, 7, 2]])
print(m)
print(m * 42)
print(m * v)
print(~m * m)

print("\nRotation test:")
z8 = ZRotationMatrix(8)
z15 = ZRotationMatrix(15)
z23 = ZRotationMatrix(23) # 23 = 15 + 8
print(z15 * z8 * ~z23)