import hashlib

inp = 'ojvtpuvg'
p = ['#'] * 8
i = 0
while True:
  s = '{}{}'.format(inp, i)
  i += 1
  k = hashlib.md5(s.encode('utf-8')).hexdigest()
  if k.startswith('00000'):
    pos = int(k[5], 16)
    #print(pos)
    if pos >= 8:
      continue
    if p[pos] != '#':
      continue
    p[pos] = k[6]
    print(p)
    if p.count('#') == 0:
      break
print(''.join(p))
