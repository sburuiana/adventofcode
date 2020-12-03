#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define mp make_pair
#define CHECK(x) if(!(x)) return false;
#define CHECKRET(x, y) if(!(x)) return (y);
#define SKIP(x) if((x)) continue;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;

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

//map<int, map<int, char> > mat;
char mat[1000][200][200], mat2[1000][200][200];
int N, M;

set<int> visitedLevels;
set<int> visitedLevels2;

/*string hsh() {
  string s;
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
      s.push_back(mat[i][j]);
  return s;
}*/

int x;
int is(int lvl, int a, int b) {
  ++x;
  return mat[lvl][a][b] == '#';
}

int ngh(int lvl, int a, int b) {
  x = 0;
  int s = 0;
  for (int i = a - 1; i <= a + 1; ++i)
    for (int j = b - 1; j <= b + 1; ++j) {
      SKIP(i == a && j == b);
      SKIP(i < 0 || j < 0 || i >= N || j >= M);
      SKIP(i == 2 && j == 2);
      SKIP(abs(i - a) + abs(j - b) != 1);
      s += is(lvl, i, j);
    }
  if (a == 0) s += is(lvl - 1, 1, 2);
  if (a == N - 1) s += is(lvl - 1, 3, 2);
  if (b == 0) s += is(lvl - 1, 2, 1);
  if (b == M - 1) s += is(lvl - 1, 2, 3);
  if (a == 1 && b == 2) {
    for (int i = 0; i < M; ++i)
      s += is(lvl + 1, 0, i);
  }
  if (a == 3 && b == 2) {
    for (int i = 0; i < M; ++i)
      s += is(lvl + 1, N - 1, i);
  }
  if (a == 2 && b == 1) {
    for (int i = 0; i < N; ++i)
      s += is(lvl + 1, i, 0);
  }
  if (a == 2 && b == 3) {
    for (int i = 0; i < N; ++i)
      s += is(lvl + 1, i, M - 1);
  }
  //cout << "Tile " << a << " " << b << " has " << x << " neighbors " << endl;
  return s;
}

void evolve(int lvl) {
  if (visitedLevels2.count(lvl)) return;
  visitedLevels2.insert(lvl);
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j) {
      SKIP(i == 2 && j == 2);
      int n = ngh(lvl, i, j);
      if (mat[lvl][i][j] == '#') {
        if (n != 1) mat2[lvl][i][j] = '.';
        else mat2[lvl][i][j] = '#';
      }
      else {
        if (n == 1 || n == 2) mat2[lvl][i][j] = '#';
        else mat2[lvl][i][j] = '.';
      }
    }
}

void copiaza(int lvl) {
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
      mat[lvl][i][j] = mat2[lvl][i][j];
}

void prnt(int lvl) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j)
      putchar(mat[lvl][i][j]);
    puts("");
  }
}

int cnt(int lvl) {
  int s = 0;
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
      s += is(lvl, i, j);
  return s;
}

/*
LL bio() {
  LL s = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      SKIP(mat[i][j] != '#');
      s += (1LL << (i * M + j));
    }
  }
  return s;
}
*/

int main() {
  freopen("fis.in", "r", stdin);
  //freopen("fis.out", "w", stdout);
  vector<string> lines = getAllLines();
  memset(mat, '.', sizeof mat);
  N = (int)lines.size();
  M = (int)lines[0].size();
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
      mat[500][i][j] = lines[i][j];
  //set<string> s;
  //s.insert(hsh());
  visitedLevels.insert(500);
  for(int _ = 0; _ < 200; ++_) {
    int ans = 0;
    //prnt(); puts("");
    visitedLevels2.clear();
    for (const auto &lvl : visitedLevels) {
      evolve(lvl - 1);
      evolve(lvl);
      evolve(lvl + 1);
    }
    for (const auto &lvl : visitedLevels2) {
      copiaza(lvl);
      ans += cnt(lvl);
    }
    cout << ans << endl;
    visitedLevels = visitedLevels2;
    /*
    string h = hsh();
    if (s.count(h)) {
      cout << bio() << endl;
      break;
    }
    s.insert(h);
    */
  }
  return 0;
}
