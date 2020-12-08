lines = open('in').read().split('\n')
ans = 0

sid = 0
nrlet = ord('z') - ord('a') + 1

def func(c):
  if c == '-':
    return ' '
  x = (ord(c) - ord('a')) + sid
  x %= nrlet
  x += ord('a')
  return chr(x)


for line in lines:
  sc, e = line[::-1].split('-', 1)
  e = e[::-1]
  sc = sc[::-1]
  sid, c = int(sc[:sc.find('[')]), sc[sc.find('[')+1:sc.find(']')]
  d = {}
  for l in e:
    if not l.isalpha():
      continue
    if l not in d:
      d[l] = 0
    d[l] += 1
  x = []
  for key in d:
    x.append((-d[key], key))
  x.sort()
  actualc = ''
  for i in range(5):
    actualc += x[i][1]
  #print(c, actualc)
  if actualc == c:
    ans += sid
  e = ''.join([func(x) for x in e])
  if 'north' in e:
    print('Part 2', e, sid)

print('Part 1', ans)
