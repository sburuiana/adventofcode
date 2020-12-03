d = eval(open('in').read())

def cnt(x):
  s = 0
  if str(x)[0] == '[':
    for y in x:
      s += cnt(y)
  elif str(x)[0] == '{':
    for key in x:
      s += cnt(key)
      s += cnt(x[key])
  else:
    try:
      y = int(x)
      s += y
    except:
      pass
  return s

print(cnt(d))
