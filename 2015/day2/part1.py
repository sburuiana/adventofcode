s = 0
for line in open('in'):
  l, w, h = [int(x) for x in line.split('x')]
  z = 2*l*w + 2*w*h + 2*h*l + min(l * w, w * h, h * l)
  s += z
print(s)
