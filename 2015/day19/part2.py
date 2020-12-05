import heapq
import re
import random

oo = 69696969696969696969
mol = 'ORnPBPMgArCaCaCaSiThCaCaSiThCaCaPBSiRnFArRnFArCaCaSiThCaCaSiThCaCaCaCaCaCaSiRnFYFArSiRnMgArCaSiRnPTiTiBFYPBFArSiRnCaSiRnTiRnFArSiAlArPTiBPTiRnCaSiAlArCaPTiTiBPMgYFArPTiRnFArSiRnCaCaFArRnCaFArCaSiRnSiRnMgArFYCaSiRnMgArCaCaSiThPRnFArPBCaSiRnMgArCaCaSiThCaSiRnTiMgArFArSiThSiThCaCaSiRnMgArCaCaSiRnFArTiBPTiRnCaSiAlArCaPTiRnFArPBPBCaCaSiThCaPBSiThPRnFArSiThCaSiThCaSiThCaPTiBSiRnFYFArCaCaPRnFArPBCaCaPBSiRnTiRnFArCaPRnFArSiRnCaCaCaSiThCaRnCaFArYCaSiRnFArBCaCaCaSiThFArPBFArCaSiRnFArRnCaCaCaFArSiRnFArTiRnPMgArF'

rules = [line.split(' => ') for line in open('in').read().split('\n')]

def ngh(s, how):
  d = set([])
  for r in rules:
    idx = s.find(r[how])
    while idx >= 0:
      x = s[:idx] + r[1 - how] + s[idx + len(r[how]):]
      d.add(x)
      idx = s.find(r[how], idx + 1)
  return d
  
def tryOnce():
  x = mol
  cnt = 0
  while True:
    n = list(ngh(x, 1))
    if len(n) == 0: break
    x = random.choice(n)
    cnt += 1
  if x != 'e': cnt = oo
  return cnt

best = oo
for _ in range(1000):
  best = min(best, tryOnce())

print(best)
