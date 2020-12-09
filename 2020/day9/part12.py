lines = [int(x) for x in open('in').read().split('\n')]

def p1():
  for n in range(25, len(lines)):
    flag = False
    for i in range(n - 25, n):
      if i < 0:
        continue
      for j in range(i, n):
        if lines[i] + lines[j] == lines[n]:
          flag = True
    if not flag:
      return lines[n]

tar = p1()
print('Part 1', tar)


def p2():
  l = 0
  r = 1
  s = lines[l]

  while True:
    if s == tar:
      return min(lines[l:r]) + max(lines[l:r])
    if s < tar:
      s += lines[r]
      r += 1
    if s > tar:
      s -= lines[l]
      l += 1

print('Part 2', p2())
