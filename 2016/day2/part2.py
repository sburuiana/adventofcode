lines = open('in').read().split('\n')
d = {
  'U' : (-1, 0),
  'R' : (0, 1),
  'D' : (1, 0),
  'L' : (0, -1),
  }
s = ''
grid = '''
             
    1      
   234     
  56789    
   ABC     
    D       
            
'''.split('\n')
for i in range(len(grid)):
  for j in range(len(grid[i])):
    if grid[i][j] == '5':
      x, y = i, j
for line in lines:
  for c in line:
    x += d[c][0]
    y += d[c][1]
    if grid[x][y] == ' ':
      x -= d[c][0]
      y -= d[c][1]
  s += grid[x][y]
print(s)
