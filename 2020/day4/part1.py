s = 0
t = open('in').read().split('++++++++++++++++')

for x in t:
  d = {}
  for y in x.split():
    a, b = y.split(':')
    d[a] = b
  if len(d) == 8:
    s += 1
  elif len(d) == 7 and 'cid' not in d:
    s += 1

print(s)

