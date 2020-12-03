s = 0
for line in open('in'):
  line = line.strip()
  a = len(line)
  line = eval(line)
  b = len(line)
  s += abs(a - b)
print(s)
