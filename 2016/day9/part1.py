s = open('in').read()
si = 0
while True:
  l = s.find('(', si)
  if l < 0:
    break
  r = s.find(')', l)
  [a, b] = [int(x) for x in s[l + 1:r].split('x')]
  s0, s1, s2 = s[:l], s[r + 1:r + 1 + a], s[r + 1 + a:]
  s1 = s1 * b
  s = s0 + s1 + s2
  si = len(s0) + len(s1)
print(len(s))
