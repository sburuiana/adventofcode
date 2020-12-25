import re

a = 2084668
b = 3704642

x = 1
lsz = 0
while x != a:
  x *= 7
  x %= 20201227
  lsz += 1
print(lsz)

x = 1
for _ in range(lsz):
  x *= b
  x %= 20201227
print(x)
