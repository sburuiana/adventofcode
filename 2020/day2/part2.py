s = 0
for line in open('in'):
 l = line.split()
 [m, M] = l[0].split('-')
 lt = l[1][0]
 m = int(m)
 M = int(M)
 if (l[2][m - 1] == lt) + (l[2][M - 1] == lt) == 1:
  s += 1
print(s)
