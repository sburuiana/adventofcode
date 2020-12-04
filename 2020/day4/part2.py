s = 0
t = open('in').read().split('++++++++++++++++')

def ok(x):
  return ord('0') <= ord(x) <= ord('9') or ord('a') <= ord(x) <= ord('f')

def vfield(k, v):
  if k == 'byr':
    return v.isnumeric() and 1920 <= int(v)  <= 2002
  if k == 'iyr':
    return v.isnumeric() and 2010 <= int(v)  <= 2020
  if k == 'eyr':
    return v.isnumeric() and 2020 <= int(v)  <= 2030
  if k == 'hgt':
    if v[-2:] == 'cm':
      return v[:-2].isnumeric() and 150 <= int(v[:-2])  <= 193
    if v[-2:] == 'in':
      return v[:-2].isnumeric() and 59 <= int(v[:-2])  <= 76
    return False
  if k == 'hcl':
    return v[0] == '#' and all([ok(v[i]) for i in range(1, len(v))])
  if k == 'ecl':
    return v in 'amb blu brn gry grn hzl oth'.split()
  if k == 'pid':
    return len(v) == 9 and v.isnumeric()
  if k == 'cid':
    return True
  return False


for x in t:
  d = {}
  for y in x.split():
    a, b = y.split(':')
    d[a] = b
  #print([(vfield(k, d[k]), k) for k in d])
  if len(d) == 8 and all([vfield(k, d[k]) for k in d]):
    s += 1
  elif len(d) == 7 and 'cid' not in d and all([vfield(k, d[k]) for k in d]):
    s += 1

print(s)

