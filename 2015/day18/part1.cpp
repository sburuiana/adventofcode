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

vector<int> v;
int N;

int usedtar;
int bkt(int lvl, int tar, int used) {
  if (tar < 0) return 0;
  if (lvl == N) return (tar == 0) && (used == usedtar);
  return bkt(lvl + 1, tar - v[lvl], used + 1) + bkt(lvl + 1, tar, used);
}

int bkt2(int lvl, int tar, int used) {
  if (tar < 0) return INT_MAX;
  if (lvl == N) {
    if (tar == 0) return used;
    return INT_MAX;
  }
  return min(bkt2(lvl + 1, tar - v[lvl], used + 1), bkt2(lvl + 1, tar, used));
}

int n, m;
vector<string> mat;

int cntNgh(int i, int j) {
  int cnt = 0;
  for(int di = -1; di <= 1; ++di)
    for (int dj = -1; dj <= 1; ++dj) {
      int ni = i + di, nj = j + dj;
      SKIP(abs(di) + abs(dj) == 0);
      SKIP(ni < 0 || ni >= n);
      SKIP(nj < 0 || nj >= m);
      cnt += (mat[ni][nj] == '#');
    }
  return cnt;
}

int howmanyon() {
  int cnt = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      if (mat[i][j] == '#') ++cnt;
  return cnt;
}

void printMe() {
  for (int i = 0; i < n; ++i)
    puts(mat[i].c_str());
  puts("");
}

int main() {
  freopen("in", "r", stdin);
  mat = getAllLines();
  n = mat.size(), m = mat[0].size();
  vector<string> aux = mat;
  int steps = 100;
  while (steps--) {
    aux = mat;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j) {
        int ngh = cntNgh(i, j);
        if (mat[i][j] == '#' && (!(ngh == 2 || ngh == 3))) aux[i][j] = '.';
        if (mat[i][j] == '.' && ngh == 3) aux[i][j] = '#';
      }
    mat.swap(aux);
    //printMe();
  }
  printf("%d\n", howmanyon());
  return 0;
}
