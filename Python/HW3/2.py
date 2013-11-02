class Student(object):
    def __init__(self, name, grades=None):
        if not grades: grades = []
        self._name = name
        self._grades = []
        self.add(grades)

    def append(self, grade):
        def to_number(s):
            try:
                return int(s)
            except ValueError:
                try:
                    return float(s)
                except:
                    pass

        if to_number(grade):
            self._grades.append(to_number(grade))

    def add(self, grades):
        for g in grades:
            self.append(g)

    def mean(self):
        if self._grades:
            return sum(self._grades) / len(self._grades)
        else:
            return 0

    def __repr__(self):
        return "%s: %s" % (self._name, " ".join(map(str, self._grades)))


class Database(object):
    def __init__(self, filename):
        self._students = {}

        with open(filename, "r") as file:
            for line in file.readlines():
                student_line = line.split(':')
                self.append(Student(student_line[0], student_line[1].strip().split(' ')))

    def append(self, student):
        """
        Добавляет студента в базу данных
        """
        self._students[student._name] = student

    def delete(self, name):
        """
        Удаляет студента из базы данных
        """
        try:
            del self._students[name]
        except KeyError:
            pass

    def __repr__(self):
        return "{0}\n".format("\n".join([str(s) for s in self._students.values()]))

    def save(self, filename):
        """
        Сохраняет базу данных в файл
        @param filename: имя файла для сохранения
        """
        with open(filename, "w") as file:
            for student in self._students.values():
                file.write("%s\n" % student)

    def best_students(self):
        """
        Находит студента (студентов) с наивысшим средним баллом
        """
        the_best = max(self._students.values(), key=lambda student: student.mean())
        yield from filter(lambda k: k.mean() == the_best.mean(), self._students.values())


db = Database("db.txt")
print(db)
for st in db.best_students():
    print(st)

db.save("d.txt")
