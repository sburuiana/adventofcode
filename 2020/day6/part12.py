s1 = 0
s2 = 0

for g in open('in').read().split('\n\n'):
  t = g.split('\n')
  k = {}
  for p in t:
    for c in p:
      if c not in k:
        k[c] = 0
      k[c] += 1
  s1 += len(k)
  for key in k:
    if k[key] == len(t):
      s2 += 1

print('Part 1', s1)
print('Part 2', s2)
