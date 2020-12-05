v = [int(x.replace('B', '1').replace('F', '0').replace('R', '1').replace('L', '0'), 2) for x in open('in').read().split('\n')]
v.sort()
print('Part 1', max(v))
for i, x in enumerate(v[1:], start = 1):
  if v[i] - v[i - 1] == 2:
    print('Part 2', v[i] - 1)
