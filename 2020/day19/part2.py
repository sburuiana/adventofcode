import re

buf = open('in').read()
buf = buf.replace('8: 42', '8: 42 | 42 8').replace('11: 42 31', '11: 42 31 | 42 11 31')
[rules, strs] = buf.split('\n\n')

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

for key in d:
  if key not in rgx:
    print(key, d[key])


rgx[8] = '({})+'.format(rgx[42])
a = []
for i in range(1, 20):
  a.append('(' + '({})'.format(rgx[42]) * i + '({})'.format(rgx[31]) * i + ')')
rgx[11] = '|'.join(a)
rgx[0] = '({})({})'.format(rgx[8], rgx[11])

c = 0
for s in strs.split('\n'):
  if re.fullmatch(rgx[0], s):
   c += 1
print(c)
