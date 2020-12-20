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

vector<string> lines;
int N = 10, M = 10;

struct tile {
  int id = 0;
  vector<string> mat;
  void read(int fline) {
    sscanf(lines[fline].c_str(), "Tile %d", &id);
    for (int i = 0; i < N; ++i) {
      mat.push_back(lines[fline + i + 1]);
    }
  }
  void hflip() {
    for (int i = 0; i < N; ++i)
      for (int l = 0, r = M - 1; l < r; ++l, --r)
        swap(mat[i][l], mat[i][r]);
  }
  void rotate() {
    vector<string> mat2 = mat;
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < M; ++j) {
        //(x, y) --> -y, x
        int ni = N - 1 - j, nj = i;
        mat2[ni][nj] = mat[i][j];
      }
    mat.swap(mat2);
  }
};

vector<tile*> tiles;
vector<pii> idx;
int used[20][20];

bool matchesEdges(int i, int j) {
  if (i > 0) {
    for (int jj = 0; jj < M; ++jj) {
      CHECK(tiles[used[i][j]]->mat[0][jj] == tiles[used[i - 1][j]]->mat[N - 1][jj]);
    }
  }
  if (j > 0) {
    for (int ii = 0; ii < N; ++ii) {
      CHECK(tiles[used[i][j]]->mat[ii][0] == tiles[used[i][j - 1]]->mat[ii][M - 1]);
    }
  }
  return true;
}

vector<string> img;

void mkimg() {
  img.clear();
  for (int line = 0; line < 12; ++line)
    for (int i = 1; i < 9; ++i) {
      string s;
      for (int col = 0; col < 12; ++col)
        for (int j = 1; j < 9; ++j)
          s += tiles[used[line][col]]->mat[i][j];
      //cout << s << endl;
      img.push_back(s);
    }
}

vector<string> seaMonster;

bool haveSeaMonsterAt(int x, int y) {
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < (int)seaMonster[i].size(); ++j) {
      SKIP(seaMonster[i][j] == ' ');
      CHECK(x + i < (int)img.size());
      CHECK(y + j < (int)img[i].size());
      CHECK(img[x + i][y + j] == seaMonster[i][j]);
    }
  return true;
}

int seaMonsters() {
  int sm = 0;
  for (int i = 0; i < (int)img.size(); ++i)
    for (int j = 0; j < (int)img[i].size(); ++j)
      sm += haveSeaMonsterAt(i, j);
  return sm;
}

LL bkt(int i, int j) {
  if (i >= 12) {
    LL res = 1;
    res *= tiles[used[0][11]]->id;
    res *= tiles[used[11][11]]->id;
    res *= tiles[used[11][0]]->id;
    res *= tiles[used[0][0]]->id;
    mkimg();
    int sm = seaMonsters();
    printf("Have match with %d sea monsters\n", sm);
    if (sm == 0) return -1;
    int cnt = 0;
    for (auto& s : img)
      for (auto& c : s)
        cnt += (c == '#');
    return 0LL + cnt - 1LL * sm * 15;
  }
  if (j >= 12)
    return bkt(i + 1, 0);
  for (int ii = 0; ii < 144; ++ii) {
    SKIP(idx[ii].first >= 0);
    idx[ii] = mp(i, j);
    used[i][j] = ii;
    for (int x = 0; x < 2; ++x, tiles[ii]->hflip())
      for (int y = 0; y < 4; ++y, tiles[ii]->rotate()) {
        SKIP(!matchesEdges(i, j));
        LL res = bkt(i, j + 1);
        SKIP(res < 0);
        return res;
      }
    idx[ii] = mp(-1, -1);
  }
  return -1;
}

int main() {
  seaMonster.push_back("                  # ");
  seaMonster.push_back("#    ##    ##    ###");
  seaMonster.push_back(" #  #  #  #  #  #   ");
  freopen("in", "r", stdin);
  freopen("out", "w", stdout);
  lines = getAllLines();
  for (int l = 0; l < (int)lines.size(); l += N + 1) {
    SKIP(lines[l].size() < 10);
    tiles.push_back(new tile());
    tiles.back()->read(l);
  }
  idx.resize(tiles.size(), mp(-1, -1));
  printf("%I64d\n", bkt(0, 0));
  return 0;
}
