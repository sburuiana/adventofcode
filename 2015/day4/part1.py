import hashlib

inp = 'bgvyzdsv'
i = 0
while True:
  s = '{}{}'.format(inp, i)
  k = hashlib.md5(s.encode('utf-8')).hexdigest()
  if k.startswith('00000'):
    print(k, i)
    break
  i += 1
