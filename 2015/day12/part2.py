d = eval(open('in').read())

def cnt(x):
  s = 0
  if str(x)[0] == '[':
    for y in x:
      s += cnt(y)
  elif str(x)[0] == '{':
    ss = 0
    red = False
    for key in x:
      if x[key] == 'red':
        red = True
        break
      ss += cnt(key)
      ss += cnt(x[key])
    if not red:
      s += ss
  else:
    try:
      y = int(x)
      s += y
    except:
      pass
  return s

print(cnt(d))
