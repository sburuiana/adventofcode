#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define mp make_pair
#define CHECK(x) if(!(x)) return false;
#define CHECKRET(x, y) if(!(x)) return (y);
#define SKIP(x) if((x)) continue;
typedef pair<int, int> pii;

vector<string> getAllLines() {
  vector<string> v;
  string s;
  while (getline(cin, s)) {
    SKIP(s.size() <= 0);
    v.push_back(s);
  }
  return v;
}

vector<int> tokenize(string s, char by) {
  replace(s.begin(), s.end(), by, ' ');
  int x, aux;
  vector<int> P;
  for (int offset = 0; sscanf(s.c_str() + offset, "%d%n", &x, &aux) >= 0; offset += aux, P.push_back(x));
  return P;
}

int toInt(string s) {
  int x;
  sscanf(s.c_str(), "%d", &x);
  return x;
}

const int MAXBUF = 2000;
char action[MAXBUF], state[MAXBUF];
const int N = 1010;
int grid[N][N];

int main() {
  freopen("in", "r", stdin);
  int l, u, r, d;
  while (scanf("%s %s %d,%d through %d,%d", action, state, &l, &u, &r, &d) != EOF) {
    for (int i = l; i <= r; ++i)
      for (int j = u; j <= d; ++j) {
        if (action[1] == 'o') grid[i][j] += 2;
        else if (state[1] == 'n') grid[i][j] += 1;
        else if(grid[i][j] > 0) grid[i][j] -= 1;
      }
  }
  LL s = 0;
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      s += grid[i][j];
  printf("%I64d\n", s);
  return 0;
}
