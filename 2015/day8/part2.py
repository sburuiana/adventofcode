s = 0
for line in open('in'):
  line = line.strip()
  a = line
  line =  repr(line).replace('"', '\\"')
  b = line
  print(a, b, len(a), len(b))
  s += abs(len(a) - len(b))
print(s)
