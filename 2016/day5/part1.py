import hashlib

inp = 'ojvtpuvg'
p = ''
i = 0
while True:
  s = '{}{}'.format(inp, i)
  k = hashlib.md5(s.encode('utf-8')).hexdigest()
  if k.startswith('00000'):
    p += k[5]
    if len(p) >= 8:
      break
  i += 1
print(p)

