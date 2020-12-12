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

char mat[1000][1000];
int inp = 1362;

bool isWall(int x, int y) {
  int k = x * x + 3 * x + 2 * x * y + y + y * y;
  k += inp;
  return __builtin_popcount(k) % 2 == 1;
}

int d[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

int main() {
  freopen("in", "r", stdin);
  int x = 0, y = 0;
  //int di = 0;
  int wx = 10, wy = -1;
  for (string& line : getAllLines()) {
    char c;
    int w;
    sscanf(line.c_str(), " %c%d", &c, &w);
    int h = 0;
    switch (c) {
    case 'F':
      x += w  * wx, y += w * wy;
      break;
    case 'N':
      wy -= w;
      break;
    case 'E':
      wx += w;
      break;
    case 'W':
      wx -= w;
      break;
    case 'S':
      wy += w;
      break;
    case 'R':
      h = w / 90;
      for (int i = 0; i < h; ++i) {
        swap(wx, wy);
        wx = -wx;
      }
      break;
    case 'L':
      h = w / 90;
      for (int i = 0; i < 4 - h; ++i) {
        swap(wx, wy);
        wx = -wx;
      }
      break;
    }
  }
  printf("%d\n", abs(x) + abs(y));
  return 0;
}
