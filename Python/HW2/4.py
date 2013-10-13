# python3.3
#coding: utf-8
# Google domain statistics

import re
from urllib.request import Request, urlopen

query = "Google chrome"
query = "+".join(query.split())

url = "http://www.google.ru/search?num=100&q="
request = Request(url + query, headers={'User-Agent': "Safari"})
page = urlopen(request).read()

site_regexp = re.compile("<cite>.*?</cite>")
domain_regexp = re.compile("\.[a-z]+/", re.IGNORECASE)

statistic = {}
for site in site_regexp.findall(str(page)):
    for domain in domain_regexp.findall(str(site)):
        domain = domain.strip('./')
        if domain in statistic:
            statistic[domain] += 1
        else:
            statistic[domain] = 1

print(statistic)