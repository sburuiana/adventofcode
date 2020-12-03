a = []
for line in open('in').read().split('\n'):
  a.append(int(line))

n = len(a)

for i in range(n):
  for j in range(i + 1, n):
      x = a[i]
      y = a[j]
      if x + y == 2020:
        print(x * y)
