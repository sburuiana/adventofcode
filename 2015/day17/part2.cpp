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

int main() {
  freopen("in", "r", stdin);
  int x;
  while (scanf("%d", &x) != EOF) v.push_back(x);
  N = (int)v.size();
  usedtar = bkt2(0, 150, 0);
  printf("%d\n", bkt(0, 150, 0));
  return 0;
}
