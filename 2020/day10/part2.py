v = [int(x) for x in open('in').read().split('\n')]
v.append(0)
v.sort()
n = len(v)
dp = [0] * n
dp[0] = 1

for i in range(1, n):
  for j in range(i):
    if (v[i] - v[j] <= 3):
      dp[i] += dp[j]
      print(v[i], v[j], dp[i], dp[j])

print(dp[n - 1])
