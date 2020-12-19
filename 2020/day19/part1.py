import re

[rules, strs] = open('in').read().split('\n\n')

d = {}
rgx = {}

for rule in rules.split('\n'):
  if len(rule) < 2:
    continue
  n, r = rule.split(':')
  n = int(n)
  if '"' in r:
    d[n] = eval(r)
    rgx[n] = d[n]
    continue
  #print(n, r)
  a = []
  for tok in r.split(' | '):
    x = tok.strip()
    a.append([int(y) for y in x.split()])
  d[n] = a

def convert(key):
  a = []
  for pos in d[key]:
    b = []
    for x in pos:
      if x not in rgx:
        return False
      b.append('({})'.format(rgx[x]))
    a.append(''.join(b))
  rgx[key] = '|'.join(a)
  return True

flag = True
while flag:
  flag = False
  for key in d:
    if key in rgx:
      continue
    if convert(key):
      flag = True

print(len(rgx), len(d))

c = 0
for s in strs.split('\n'):
  if re.fullmatch(rgx[0], s):
    c += 1
print(c)
