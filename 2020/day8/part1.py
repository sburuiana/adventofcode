prog = open('in').read().split('\n')

eip = 0
acc = 0

ran = set([])

while eip >= 0 and eip < len(prog):
  [i, p] = prog[eip].split()
  if eip in ran:
    print(acc)
    exit(0)
  ran.add(eip)
  if i == 'acc':
    acc += int(p)
    eip += 1
  elif i == 'jmp':
    eip += int(p)
  elif i == 'nop':
    eip += 1
