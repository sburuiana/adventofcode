s = 0
for line in open('in'):
  l, w, h = [int(x) for x in line.split('x')]
  z = 2 * min(l + w, w + h, h + l) + l * w * h
  s += z
print(s)
