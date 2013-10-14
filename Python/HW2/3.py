#python3.3
#coding: utf-8
# RSS
from xml.etree import ElementTree

indent = "    "


def print_rss(parent, level):
    print((level * indent + "<level {0:d}>").format(level))
    if parent.text:
        lines = parent.text.split("\n")
        for line in lines:
            print(level * indent + line)
            # print(line)
        for child in parent:
            print_rss(child, level + 1)


rss = "http://feedparser.org/docs/examples/atom10.xml"
# rss_file = urlopen(rss)
rss_file = open("rss.xml", mode="r")
tree = ElementTree.parse(rss_file)
root = tree.getroot()
print_rss(root, 0)
