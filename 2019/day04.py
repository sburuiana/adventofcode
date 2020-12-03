
l = 124075
r = 580769

def check(p):
  s = str(p)
  flag = False
  for i in range(len(s) - 1):
    if s[i] == s[i +1]:
      if i > 0 and s[i - 1] == s[i + 1]:
        pass
      elif i < len(s) - 2 and s[i] == s[i + 2]:
        pass
      else:
        flag = True
  if not flag:
    return False
  return sorted(s) == list(s)


cnt = 0
for p in range(l, r + 1):
  if check(p):
    cnt += 1
  pass
print(check(111111))
print(check(223450))
print(check(123789))
print(cnt)
