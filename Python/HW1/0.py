# coding=utf-8
# python 3.3
# существительные в "Войне и мире"

import codecs, pymorphy2, datetime, string

t1 = datetime.datetime.now()
morph = pymorphy2.MorphAnalyzer()


def words(file):
    for line in file:
        yield from line.split()


def is_noun(s):
    for p in morph.parse(s):
        if 'NOUN' in p.tag:
            return True
    return False


def clear_word(s):
    return s.strip(string.punctuation)

c = 0
with codecs.open("wap.txt", encoding="utf-8", mode="r") as f:
    for word in words(f):
        if is_noun(clear_word(word)):
            c += 1

print("Nouns count: %s" % c)

t2 = datetime.datetime.now()
print("Execution time: %s" % (t2 - t1))
