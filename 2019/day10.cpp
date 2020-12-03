#ifdef _WIN32

#endif
#ifdef ON_WINDOWS
#include <Windows.h>
#endif
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

int toInt(const string &s) {
  int x;
  sscanf(s.c_str(), "%d", &x);
  return x;
}

vector<int> tokenize(string &s, char by) {
  vector<int> v;
  return v;
}

char mat[200][200];
int N, M;

int refx = 0, refy = 0;

int getCadran(pii f) {
  f.first -= refx;
  f.second -= refy;
  if (f.first < 0 && f.second >= 0) return 1;
  if (f.first >= 0 && f.second >= 0) return 2;
  if (f.first >= 0 && f.second < 0) return 3;
  else return 4;
}

struct cmp {
  bool method1(const pii &f1, const pii &f2) const {
    /*
      Broken operator (non-transitive).
      Worked by chance for part 1.
    */
    pii f11 = mp(f1.first - refx, f1.second - refy);
    pii f22 = mp(f2.first - refx, f2.second - refy);
    return f11.first * f22.second < f22.first * f11.second;
  }

  bool method2(const pii &f1, const pii &f2) const {
    pii f11 = mp(f1.first - refx, f1.second - refy);
    pii f22 = mp(f2.first - refx, f2.second - refy);
    int C1 = getCadran(f1), C2 = getCadran(f2);
    if (C1 != C2) return C1 < C2;
    return f11.first * f22.second < f22.first * f11.second;
  }

  bool operator()(const pii &f1, const pii &f2) const {
    return method2(f1, f2);
  }
};

int howMany(int x, int y) {
  refx = x, refy = y;
  set<pii, cmp> fractions;
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j) {
      SKIP(mat[i][j] == '.');
      SKIP(i == x && j == y);
      fractions.insert(mp(i, j));
    }
  return (int)fractions.size();
}

int eudist(pii a, pii b) {
  int dx = a.first - b.first;
  int dy = a.second - b.second;
  return dx * dx + dy * dy;
}

vector<pii> vaporize(int x, int y) {
  refx = x, refy = y;
  vector<pii> res;
  pii keyxy = mp(x, y);
  bool flag = true;
  set<pii> alreadyVaporized;
  while (flag) {
    set<pii, cmp> fractions;
    flag = false;
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < M; ++j) {
        SKIP(i == x && y == j);
        SKIP(mat[i][j] == '.');
        pii keyij = mp(i, j);
        SKIP(alreadyVaporized.count(keyij));
        auto it = fractions.find(keyij);
        if (it != fractions.end()) {
          if (eudist(keyxy, keyij) <= eudist(keyxy, *it)) {
            fractions.erase(it);
            fractions.insert(keyij);
          }
          else continue;
        }
        //printf("Considering %d %d which is in cadran %d\n", i, j, getCadran(keyij));
        fractions.insert(keyij);
        flag = true;
      }
    for (const auto &f : fractions) {
      res.push_back(f);
      alreadyVaporized.insert(f);
    }
  }
  return res;
}

void printMat() {
  for (int i = 0; i < N; ++i)
    puts(mat[i]);
}

#ifdef ON_WINDOWS
void setCursorPosition(int x, int y) {
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  fflush(stdout);
  COORD coord = { (SHORT)x, (SHORT)y };
  SetConsoleCursorPosition(hOut, coord);
}
#endif

void changePoint(int i, int j) {
  mat[i][j] = '.';
#ifdef ON_WINDOWS
  setCursorPosition(j, i);
  putchar('.');
#else
  for (int _ = 0; _ < 50; ++_) puts("");
  printMat();
#endif
}

void sleepFor(double secs) {
  clock_t t0 = clock();
  while (1.0 * (clock() - t0) / CLOCKS_PER_SEC < secs);
}

void visualize(pii src, vector<pii> &order) {
#ifdef ON_WINDOWS
  setCursorPosition(0, 0);
#endif
  mat[src.first][src.second] = 'X';
  printMat();
  for (const auto &it : order) {
    changePoint(it.first, it.second);
    sleepFor(0.05);
  }
}

int main() {
  freopen("fis.in", "r", stdin);
  vector<string> lines = getAllLines();
  int i = 0;
  N = (int)lines.size(), M = (int)lines[0].size();
  for (const auto &line : lines) {
    strcpy(mat[i], line.c_str());
    ++i;
  }
  pair<int, pii> mx = mp(0, mp(0, 0));
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j) {
      SKIP(mat[i][j] == '.');
      mx = max(mx, mp(howMany(i, j), mp(i, j)));
    }

  printf("Best station is at %d %d\n", mx.second.first, mx.second.second);
  printf("Part 1 : %d\n", howMany(mx.second.first, mx.second.second));
  vector<pii> res = vaporize(mx.second.first, mx.second.second);
  printf("Part 2 : %d\n", res[199].second * 100 + res[199].first);

  visualize(mx.second, res);
  return 0;
}
