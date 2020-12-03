s = 0
for line in open('in'):
 l = line.split()
 [m, M] = l[0].split('-')
 lt = l[1][0]
 if l[2].count(lt) >= int(m) and l[2].count(lt) <= int(M):
  s += 1
print(s)
