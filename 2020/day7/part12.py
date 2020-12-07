lines = open('in').read().split('\n')
G = {}
rg = {}
viz = {}

def DFS(wg, x):
  #print('Visiting', x)
  if x in viz:
    return viz[x]
  s = 1
  if x not in wg:
    wg[x] = []
  for n, y in wg[x]:
    s += n * DFS(wg, y)
  viz[x] = s
  return s

for line in lines:
  line = line.replace('.', '')
  a, b = line.split(' bags contain ')
  toks = b.split(',')
  for tok in toks:
    tok = tok.strip()
    if tok == 'no other bags':
      continue
    c, d = tok.split(' ', 1)
    c = int(c)
    d = d.replace('bags', '').replace('bag', '').strip()
    #print('Edge from', a, 'to', d)
    if a not in G:
      G[a] = []
    G[a].append((c, d))
    if d not in rg:
      rg[d] =[]
    rg[d].append((c, a))

DFS(rg, 'shiny gold')
print(len(viz) - 1)

viz = {}
print(DFS(G, 'shiny gold') - 1)
