inp = '1113122113'
for t in range(1, 51):
  t,s='E {}'.format(inp).split();l,t,o=-1,t=='E',''
  for i,c in enumerate(s[1:]+'$'):
   p=s[i]
   if t&(c!=p):o+=str(i-l)+p;l=i
   if(t|i&1)^1:o+=int(c)*p
  inp = o
  if t == 40:
    print('Part 1', len(inp))
  if t == 50:
    print('Part 2', len(inp))
