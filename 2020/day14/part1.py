lines = open('in').read().split('\n')
msk = 'X' * 36
d = {}

def f(x):
  for i in range(36):
    if msk[36 - 1 -  i] == '1':
      x |= (1 << i)
    if msk[36 - 1 - i] == '0':
      x &= (~(1 << i))
  return x

for line in lines:
  if line.startswith('mask'):
    msk = line[len('mask = '):]
    continue
  a, b = line.split(' = ')
  b = int(b)
  a = int(a[a.find('[') + 1:a.find(']')])
  #print(a, b, msk)
  d[a] = f(b)
s = 0
for key in d:
  s += d[key]
print(s)

