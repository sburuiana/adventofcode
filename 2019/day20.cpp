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

map< pair<pii, int> , int> dst;
int d[] = { 0, 1, 0, -1, 1, 0, -1, 0 };
char mat[150][150];
int N, M;
map< string, vector< pii > > tps;

string makeStr(char x1, char x2) {
  string s = "";
  s.push_back(x1);
  s.push_back(x2);
  return s;
}

bool isa(char c) {
  return c >= 'A' && c <= 'Z';
}

bool isSpace(int x, int y) {
  CHECK(x >= 0 && x < N && y >= 0 && y < M);
  CHECK(mat[x][y] == ' ');
  return true;
}

pair<string, bool> getLabel(int x, int y) {
  if (isa(mat[x][y + 1]) && isa(mat[x][y + 2]))
    return mp(makeStr(mat[x][y + 1], mat[x][y + 2]), isSpace(x, y + 3));
  if (isa(mat[x][y - 1]) && isa(mat[x][y - 2]))
    return mp(makeStr(mat[x][y - 2], mat[x][y - 1]), isSpace(x, y - 3));
  if (isa(mat[x + 1][y]) && isa(mat[x + 2][y]))
    return mp(makeStr(mat[x + 1][y], mat[x + 2][y]), isSpace(x + 3, y));
  if (isa(mat[x - 1][y]) && isa(mat[x - 2][y]))
    return mp(makeStr(mat[x - 2][y], mat[x - 1][y]), isSpace(x - 3, y));
  return mp("", 0);
}

int BFS(pii st, int MAXLVL = 100) {
  dst.clear();
  dst[mp(st, 0)] = 0;
  queue< pair<pii, int> > Q;
  Q.push(mp(st, 0));
  while (!Q.empty()) {
    pii x = Q.front().first;
    int xlvl = Q.front().second;
    //printf("%d %d %d\n", x.first, x.second, xlvl);
    Q.pop();
    for (int di = 0; di < 4 + (int)tps[getLabel(x.first, x.second).first].size(); ++di) {
      pii nx;
      int nlvl = xlvl;
      if(di < 4) nx = mp(x.first + d[di * 2], x.second + d[di * 2 + 1]);
      else {
        pair<string, bool> label = getLabel(x.first, x.second);
        nx = tps[label.first][di - 4];
        nlvl = xlvl + (label.second ? 1 : (-1));
      }
      SKIP(nx == x);
      SKIP(dst.count(mp(nx, nlvl)));
      SKIP(nlvl >= MAXLVL);
      SKIP(nlvl < 0);
      SKIP(mat[nx.first][nx.second] != '.');
      dst[mp(nx, nlvl)] = dst[mp(x, xlvl)] + 1;
      Q.push(mp(nx, nlvl));
    }
  }
  return dst[mp(tps["ZZ"][0], 0)];
}

int main() {
  freopen("fis.in", "r", stdin);
  freopen("fis.out", "w", stdout);
  vector<string> lines = getAllLines();
  N = (int)lines.size();
  M = 0;
  for (const auto &it : lines) {
    M = max(M, (int)it.size());
  }
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j) {
      mat[i][j] = ((j < (int)lines[i].size()) ? lines[i][j] : '*');
    }
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j) {
      SKIP(mat[i][j] != '.');
      pair<string, bool> s = getLabel(i, j);
      SKIP(s.first.empty());
      tps[s.first].push_back(mp(i, j));
    }
  printf("%d\n", BFS(tps["AA"][0]));
  return 0;
}
