vals = {}

instr = {}

def getval(x):
  if x.isnumeric():
    return int(x)
  if x not in vals:
    vals[x] = evl(instr[x])
  return vals[x]

def evl(x):
  toks = x.split()
  if len(toks) == 1:
    return getval(x)
  if len(toks) == 2:
    return ~getval(toks[1])
  x, op, y = toks
  if op == 'AND':
    return getval(x) & getval(y)
  if op == 'LSHIFT':
    return getval(x) << getval(y)
  if op == 'RSHIFT':
    return getval(x) >> getval(y)
  if op == 'OR':
    return getval(x) | getval(y)

for line in open('in'):
  f, t = line.strip().split(' -> ')
  instr[t] = f

x = getval('a')
vals = {}
instr['b'] = str(x)
print(getval('a'))
