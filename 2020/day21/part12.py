import re

v = open('in').read().split('\n')
ingr = {}
alg = {}
appearsOnSameLineIngr = {}
appearsOnSameLineAlg = {}
lines = []
for line in v:
  x, y = line.split(' contains ')
  x = x.split()
  y = y.split()
  lines.append((x, y))
  for i in x:
    if i not in ingr:
      ingr[i] = 0
    ingr[i] += 1
    for a in y:
      if a not in alg:
        alg[a] = 0
      alg[a] += 1
      if i not in appearsOnSameLineIngr:
        appearsOnSameLineIngr[i] = set([])
      if a not in appearsOnSameLineAlg:
        appearsOnSameLineAlg[a] = set([])
      appearsOnSameLineIngr[i].add(a)
      appearsOnSameLineAlg[a].add(i)

def canPossiblyContain(i, a):
  for x, y in lines:
    if a in y and i not in x:
      #print('{} can not contain {} because of rule {} contains {}'.format(i, a, x, y))
      return False
  #print('{} can contain {}'.format(i, a))
  return True

#print(alg)

cnt = 0

G = {}

for i in ingr:
  flag = False
  for a in alg:
    if canPossiblyContain(i, a):
      if a not in G:
        G[a] = []
      G[a].append(i)
      flag = True
  if not flag:
    #print('Got ingrediect {} (+ {})'.format(i, ingr[i]))
    cnt += ingr[i]

print('Part 1', cnt)

leftPair = {}
rightPair = {}

def pairUp(x):
  if x in viz:
    return None
  viz.add(x)
  for y in G[x]:
    if y not in rightPair:
      leftPair[x] = y
      rightPair[y] = x
      return y
  for y in G[x]:
    if pairUp(rightPair[y]):
      leftPair[x] = y
      rightPair[y] = x
      return y
  return None

flag = True
while flag:
  flag = False
  viz = set([])
  for key in alg:
    if key not in leftPair:
      if pairUp(key) is not None:
        flag = True

matched = []
for a in leftPair:
  matched.append((leftPair[a], a))

#print(matched)
matched.sort(key = lambda x : x[1])
matched = [x[0] for x in matched]
print('Part 2', ','.join(matched))
