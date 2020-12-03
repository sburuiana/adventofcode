#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define mp make_pair
#define CHECK(x) if(!(x)) return false;
#define CHECKRET(x, y) if(!(x)) return (y);
#define SKIP(x) if((x)) continue;
typedef pair<int, int> pii;

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

char mat[30][30];

int main() {
  freopen("fis.in", "r", stdin);
  memset(mat, 0xFF, sizeof mat);
  string s;
  cin >> s;
  int N = 6, M = 25;
  int idx = 0;
  pii best = mp(INT_MAX, 0);
  while (idx < (int)s.size()) {
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < M; ++j, ++idx) {
        SKIP(mat[i][j] >= 0);
        if (s[idx] == '1') mat[i][j] = '#';
        else if (s[idx] == '0') mat[i][j] = ' ';
      }
  }
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j)
      putchar(mat[i][j]);
    puts("");
  }
  return 0;
}
