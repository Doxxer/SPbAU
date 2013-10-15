#coding: utf-8
# python3.3
# RSS
from urllib.request import urlopen
from xml.etree import ElementTree as ET

indent = "\t"


def get_attrib(node):
    attributes = list(node.attrib.items())
    if len(attributes) == 0: return ""
    attr_list = []
    for attr in attributes:
        attr_list.append("{0}=\"{1}\"".format(attr[0], attr[1]))
    return " " + " ".join(attr_list)


def print_tag(node, level, closed=False):
    if closed:
        print("%s</%s>" % (level * indent, node.tag))
    else:
        print("%s<%s%s>" % (level * indent, node.tag, get_attrib(node)))


def print_rss(node, level):
    if len(list(node)) != 0:
        print_tag(node, level)
        for child in node:
            print_rss(child, level + 1)
        print_tag(node, level, True)
    else:
        print_tag(node, level)
        text = node.text
        if text:
            for line in text.split('\n'):
                if line:
                    print("%s%s" % ((level + 1) * indent, line))
        print_tag(node, level, True)


rss = "http://logic.pdmi.ras.ru/csclub/news/rss"
rss_file = urlopen(rss)
tree = ET.parse(rss_file)
root = (tree).getroot()
print_rss(root, 0)