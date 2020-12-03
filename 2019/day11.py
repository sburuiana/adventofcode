from collections import defaultdict

ip = 0
rb = 0

def run(program, program_input):
    global ip
    global rb
    global mem
    outs = []
    while True:
        op = mem[ip] % 100
        if op == 99:
            return outs
        size = [0, 4, 4, 2, 2, 3, 3, 4, 4, 2][op]
        args = [mem[ip+i] for i in range(1, size)]
        modes = [(mem[ip] // 10 ** i) % 10 for i in range(2, 5)]
        reads = [(mem[x], x, mem[x+rb])[m] for x, m in zip(args, modes)]
        writes = [(x, None, x+rb)[m] for x, m in zip(args, modes)]
        #print(ip, op)
        ip += size
        if op == 1:
            mem[writes[2]] = reads[0] + reads[1]
        if op == 2:
            mem[writes[2]] = reads[0] * reads[1]
        if op == 3:
            if len(program_input) == 0:
              ip -= size
              return outs
            mem[writes[0]] = program_input.pop(0)
        if op == 4:
            outs.append(reads[0])
        if op == 5 and reads[0]:
            ip = reads[1]
        if op == 6 and not reads[0]:
            ip = reads[1]
        if op == 7:
            mem[writes[2]] = int(reads[0] < reads[1])
        if op == 8:
            mem[writes[2]] = int(reads[0] == reads[1])
        if op == 9:
            rb += reads[0]

d = {}
d[(0, 0)] = 1
pos = [0, 0]
facing = [-1, 0]

def rotateRight():
  global facing
  if facing == [-1, 0]:
    facing = [0, 1]
  elif facing == [0, 1]:
    facing = [1, 0]
  elif facing == [1, 0]:
    facing = [0, -1]
  else:
    facing = [-1, 0]

def rotateLeft():
  rotateRight()
  rotateRight()
  rotateRight()

program = open('in').read().strip()

mem = defaultdict(int, enumerate(map(int, program.split(','))))

while True:
  inp = 0
  if (pos[0], pos[1]) in d:
    inp = d[(pos[0], pos[1])]
  outpts = list(run(program, [inp]))
  if len(outpts) < 2:
    break
  #print(outpts, pos, facing)
  for i in range(0, len(outpts), 2):
    out = outpts[i:]
    d[(pos[0], pos[1])] = out[0]
    if out[1] == 0:
      rotateLeft()
    else:
      rotateRight()
    pos[0] += facing[0]
    pos[1] += facing[1]

A = [[' ' for _ in range(50)] for _ in range(50)]
  
for key in d:
  A[key[0]][key[1]] = '#' if (d[key] == 1) else ' '

for line in A:
  print(''.join(line))
