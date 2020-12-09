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

const int N = 6, M = 50;
char mat[N][M + 5];
char buf1[100], buf2[100];

int main() {
  freopen("in", "r", stdin);
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
      mat[i][j] = '.';
  vector<string> lines = getAllLines();
  for (auto& l : lines) {
    if (l[1] == 'e') {
      int x, y;
      sscanf(l.c_str(), "rect %dx%d", &x, &y);
      //printf("$$$$ %d %d\n", x, y);
      for (int i = 0; i < y; ++i)
        for (int j = 0; j < x; ++j)
          mat[i][j] = '#';
      continue;
    }
    int a, b;
    char which;
    sscanf(l.c_str(), "rotate %s %c=%d by %d", buf1, &which, &a, &b);
    //printf("$$$$ %s %c %d %d\n", buf1, which, a, b);
    if (buf1[0] == 'r') {
      while (b--) {
        int aux = mat[a][M - 1];
        for (int j = M - 1; j > 0; --j)
          mat[a][j] = mat[a][j - 1];
        mat[a][0] = aux;
      }
    }
    else {
      while (b--) {
        int aux = mat[N - 1][a];
        for (int i = N - 1; i > 0; --i)
          mat[i][a] = mat[i - 1][a];
        mat[0][a] = aux;
      }
    }
  }
  int s = 0;
  for (int i = 0; i < N; ++i) {
    puts(mat[i]);
    for (int j = 0; j < M; ++j)
      s += (mat[i][j] == '#');
  }
  printf("%d\n", s);
  return 0;
}
