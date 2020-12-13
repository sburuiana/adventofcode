lines = open('in').read().split('\n')
x = int(lines[0])
v = list(map(int, filter(lambda x : x.isnumeric(), lines[1].split(','))))
y = 0
while True:
  bid = None
  for n in v:
    if (x + y) % n == 0:
      bid = n
  if bid is not None:
    print(bid * y)
    break
  y += 1
