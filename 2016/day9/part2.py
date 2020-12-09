s = open('in').read()

def solve(s):
  l = s.find('(')
  if l < 0:
    return len(s)
  r = s.find(')', l)
  [a, b] = [int(x) for x in s[l + 1:r].split('x')]
  s0, s1, s2 = s[:l], s[r + 1:r + 1 + a], s[r + 1 + a:]
  return len(s0) + b * solve(s1) + solve(s2)

print(solve(s))
