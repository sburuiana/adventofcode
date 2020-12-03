mat = open('in').read().split('\n')
n = len(mat)
for i in range(n):
  mat[i] = mat[i] * 100
m = len(mat[0])

def a(r):
  s = 0
  for i in range(n):
    if i * r < m and mat[i][i * r] == '#':
      s += 1
  return s

def a2(d):
  s = 0
  for j in range(m):
    if j * d < n and mat[j * d][j] == '#':
      s += 1
  return s

x, y, z, t, u = a(1), a(3), a(5), a(7), a2(2)
print('Part 1:', y)
print('Part 2:', x * y * z * t * u)
