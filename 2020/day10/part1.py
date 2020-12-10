s = set([int(x) for x in open('in').read().split('\n')])
s.add(max(list(s)) + 3)

cur = 0
d1 = 0
d3 = 1

while len(s) > 1:
  print(len(s), cur, d1, d3)
  for x in s:
    if x - cur == 1:
      d1 += 1
      s.remove(x)
      cur = x
      break
    elif x - cur == 2:
      s.remove(x)
      cur = x
      break
    elif x - cur == 3:
      s.remove(x)
      cur = x
      d3 += 1
      break

print(d1, d3)
print(d1 * d3)
