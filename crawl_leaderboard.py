import urllib.request
import re

pts = {}
info = {}

def processEntry(page):
  print(page)
  idx = 0
  while page[idx] == ' ': idx += 1
  s = ''
  while str(page[idx]).isdigit():
    s += page[idx]
    idx += 1
  rank = int(s)
  nfo = {}
  mrk = '<span class="leaderboard-userphoto">'
  idx = page.find(mrk)
  if idx >= 0:
    mrk = '<img src="'
    idx = page.find(mrk)
    idx += len(mrk)
    imgurl = page[idx:page.find('"', idx)]
    if len(imgurl) > 20:
      nfo['imgurl'] = imgurl
  mrk = '<a href="'
  idx = page.find(mrk)
  if idx >= 0:
    idx += len(mrk)
    usrurl = page[idx:page.find('"', idx)]
    nfo['usrurl'] = usrurl
  anon = re.findall(r'anonymous user #\d+', page)
  if len(anon) > 0:
    usr = anon[0]
  else:
    page = page[::-1]
    usr = page[:page.find('</span>'[::-1])][::-1]
    usr = usr[:usr.find('<')]
  info[usr] = nfo
  if usr not in pts:
    pts[usr] = 0
  pts[usr] += 100 - rank + 1
  if len(usr.strip()) == 0:
    print('WE HAVE PROBLEM HERE')
    exit(0)

def crawl(year, day):
  print('Now crawling day {}'.format(day))
  url = 'https://adventofcode.com/{}/leaderboard/day/{}'.format(year, day)
  page = str(urllib.request.urlopen(url).read())
  open('day{}.html'.format(day), 'w').write(page)
  idx = 0
  while idx < len(page):
    mrk = '<span class="leaderboard-position">'
    idx = page.find('<span class="leaderboard-position">', idx)
    if idx < 0: break
    idx += len(mrk)
    nidx = page.find(r'</div>', idx)
    if nidx < 0: nidx = len(page)
    processEntry(page[idx:nidx])

def putStuff():
  global pts
  pts = list(pts.items())
  pts.sort(key = lambda x : -x[1])
  print('| Rank | Who | Points')
  print('|-|-|-|')
  for idx, (usr, nrpts) in enumerate(pts, start = 1):
    usrshow = usr
    if 'usrurl' in info[usr]:
      usrshow = '[{}]({})'.format(usr, info[usr]['usrurl'])
    print('|{}|{}|{}|'.format(idx, usrshow, nrpts))

def crawlAll(year):
  for day in range(2, 26):
    crawl(year, day)
    print(pts)
    print(info)

def getFromFile(fl):
  global pts
  global info
  lines = open(fl).read().split('\n')
  pts = eval(lines[0])
  info = eval(lines[1])

crawlAll(2019)
putStuff()
