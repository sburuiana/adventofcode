#include <Windows.h>
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

const int MAXN = 85;
char mat[MAXN][MAXN];
int N, M;
map<int, int> dst[MAXN][MAXN];

int d[] = { 0, 1, 0, -1, 1, 0, -1, 0 };

int BFS(pii x) {
  //memset(dst, 0xFF, sizeof dst);
  queue< pair<pii, int> > Q;
  Q.push(mp(x, 0));
  dst[x.first][x.second][0] = 0;
  pii best = mp(0, 0);
  while (!Q.empty()) {
    auto t = Q.front();
    Q.pop();
    int tx = t.first.first, ty = t.first.second,
      tm = t.second;
    for (int di = 0; di < 4; ++di) {
      int nx = tx + d[di * 2], ny = ty + d[di * 2 + 1];
      SKIP(nx >= N || nx < 0 || ny >= M || ny < 0);
      SKIP(mat[nx][ny] == '#');
      int what = mat[nx][ny] - 'A';
      if (what >= 0 && what <= 26) {
        SKIP(!(tm & (1 << what)));
      }
      int nm = tm;
      what = (mat[nx][ny] - 'a');
      if (what >= 0 && what <= 26)
        nm |= (1 << what);
      SKIP(dst[nx][ny].count(nm));
      dst[nx][ny][nm] = dst[tx][ty][tm] + 1;
      best = min(best, mp(-nm, dst[nx][ny][nm]));
      //printf("%d %d\n", best.first, best.second);
      Q.push(mp(mp(nx, ny), nm));
    }
  }
  return best.second;
}

int main() {
  freopen("fis.in", "r", stdin);
  vector<string> lines = getAllLines();
  N = (int)lines.size();
  M = (int)lines[0].size();
  pii pos;
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j) {
      mat[i][j] = lines[i][j];
      if (mat[i][j] == '@') pos = mp(i, j);
      //dst[i][j].resize((1 << 26) + 5, -1);
    }
  printf("%d\n", BFS(pos));
  return 0;
}
