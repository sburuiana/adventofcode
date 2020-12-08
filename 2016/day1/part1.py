buf = open('in').read().split(', ')
x = 0
y = 0
d = [(0, 1), (1, 0), (0, -1), (-1, 0)]
cur = 0
for t in buf:
  a, b = t[0], t[1:]
  b = int(b)
  if a == 'L':
    cur -= 1
  else:
    cur += 1
  cur %= 4
  x += d[cur][0] * b
  y += d[cur][1] * b

print(abs(x) + abs(y))
