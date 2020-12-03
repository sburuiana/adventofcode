def f1(x):
  return x // 3 - 2

def f2(x):
  a = x // 3 - 2
  if a <= 0:
    return 0
  return a + f2(a)

def solve(fl, f):
  return sum(map(lambda x : f(int(x)), open(fl).read().split()))

print(solve('in', f1))
print(solve('in', f2))
