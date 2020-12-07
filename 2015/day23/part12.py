prog = open('in').read().split('\n')
eip = 0

part = 1

reg = {}
reg['a'] = 0 if part == 1 else 1
reg['b'] = 0

def val(x):
  try:
    return int(x)
  except:
    pass
  return reg[x]

while eip >= 0 and eip < len(prog):
  instr, params = prog[eip].split(' ', 1)
  #print(prog[eip])
  params = [x.strip() for x in params.split(',')]
  if instr == 'hlf':
    reg[params[0]] //= 2
    eip += 1
  elif instr == 'tpl':
    reg[params[0]] *= 3
    eip += 1
  elif instr == 'inc':
    reg[params[0]] += 1
    eip += 1
  elif instr == 'jmp':
    eip += val(params[0])
  elif instr == 'jie':
    r, v = params[0], val(params[1])
    if val(r) % 2 == 0:
      eip += v
    else:
      eip += 1
  elif instr == 'jio':
    r, v = params[0], val(params[1])
    if val(r) == 1:
      eip += v
    else:
      eip += 1

print(reg)
