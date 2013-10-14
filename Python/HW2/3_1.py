#python3.3
#coding: utf-8
# RSS

import feedparser

rss = "http://mit.spbau.ru/news/rss"
x = feedparser.parse(rss).values()
print(x)