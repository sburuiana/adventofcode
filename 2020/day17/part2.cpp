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

char mat[2][110][110][110][110];
int N = 0, M = 0, P = 0, K = 0;
int cur = 0, old = 1;

int getOccupiedNgh(int i, int j, int k, int l) {
  int cnt = 0;
  for (int ii = i - 1; ii <= i + 1; ++ii)
    for (int jj = j - 1; jj <= j + 1; ++jj)
      for (int kk = k - 1; kk <= k + 1; ++kk)
        for (int ll = l - 1; ll <= l + 1; ++ll) {
          SKIP(jj < 0 || ii < 0 || kk < 0 || ll < 0);
          SKIP(jj >= M || ii >= N || kk >= P || ll >= K);
          SKIP(ii == i && jj == j && kk == k && ll == l);
          cnt += (mat[old][ii][jj][kk][ll] == '#');
        }
  return cnt;
}


void printMat() {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j)
      putchar(mat[cur][50][50][i][j]);
    puts("");
  }
  puts("");
}

void read() {
  for (int i = 50; ; ++i) {
    if (scanf("%s", mat[0][50][50][i] + 50) == EOF) break;
  }
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
      for (int k = 0; k < P; ++k)
        for (int l = 0; l < K; ++l)
          if (mat[0][i][j][k][l] == 0) mat[0][i][j][k][l] = '.';
}

int main() {
  freopen("in", "r", stdin);
  //freopen("out", "w", stdout);
  memset(mat, '.', sizeof mat);
  N = 100; M = 100; P = 100; K = 100;
  read();
  //printMat();
  //return 0;
  P = N;
  bool flag = true;
  for (int c = 0; c < 6; ++c) {
    flag = false;
    swap(cur, old);
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < M; ++j)
        for (int k = 0; k < P; ++k)
          for (int l = 0; l < K; ++l) {
            mat[cur][i][j][k][l] = mat[old][i][j][k][l];
            int ngh = getOccupiedNgh(i, j, k, l);
            if (mat[cur][i][j][k][l] == '.' && ngh == 3) {
              mat[cur][i][j][k][l] = '#';
              flag = true;
            }
            if (mat[cur][i][j][k][l] == '#' && !(ngh == 2 || ngh == 3)) {
              mat[cur][i][j][k][l] = '.';
              flag = true;
            }
          }
    //printMat();
    //break;
  }
  int cnt = 0;
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
      for (int k = 0; k < P; ++k)
        for (int l = 0; l < K; ++l)
          if (mat[cur][i][j][k][l] == '#')
            ++cnt;
  printf("%d\n", cnt);
  return 0;
}
