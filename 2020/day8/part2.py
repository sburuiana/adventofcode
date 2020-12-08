prog = open('in').read().split('\n')

def runprog(which):
  eip = 0
  acc = 0
  ran = set([])
  while eip >= 0 and eip < len(prog):
    [i, p] = prog[eip].split()
    if eip == which and i == 'nop':
      i = 'jmp'
    if eip == which and i == 'jmp':
      i = 'nop'
    if eip in ran:
      return None
    ran.add(eip)
    if i == 'acc':
      acc += int(p)
      eip += 1
    elif i == 'jmp':
      eip += int(p)
    elif i == 'nop':
      eip += 1
  return acc

for i in range(len(prog)):
  ret = runprog(i)
  if ret is not None:
    print(ret)
