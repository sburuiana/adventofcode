v = [(1 if x == '(' else (-1)) for x in open('in').read()]
for i in range(1, len(v)):
  v[i] += v[i - 1]
  if v[i] < 0:
    print(i + 1)
    break
