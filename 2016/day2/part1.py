lines = open('in').read().split('\n')
x = 1
y = 1
d = {
  'U' : (-1, 0),
  'R' : (0, 1),
  'D' : (1, 0),
  'L' : (0, -1),
  }
s = ''
for line in lines:
  for c in line:
    x += d[c][0]
    y += d[c][1]
    if x < 0: x = 0
    if x >= 3: x = 2
    if y < 0: y = 0
    if y >= 3: y = 2
    #print(c, x * 3 + y + 1)
  s += str(x * 3 + y + 1)
print(s)
