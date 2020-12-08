buf = open('in').read().split(', ')
x = 0
y = 0
d = [(0, 1), (1, 0), (0, -1), (-1, 0)]
cur = 0
viz = set([])
for t in buf:
  a, b = t[0], t[1:]
  b = int(b)
  if a == 'L':
    cur -= 1
  else:
    cur += 1
  cur %= 4
  for i in range(b):
    x += d[cur][0]
    y += d[cur][1]
    if (x, y) in viz:
      print(abs(x) + abs(y))
      exit(0)
    viz.add((x, y))
