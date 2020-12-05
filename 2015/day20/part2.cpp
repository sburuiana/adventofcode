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

LL presentsTo(int house, int elf) {
  CHECKRET(house % elf == 0, 0);
  CHECKRET(1LL *elf * 50 >= house, 0);
  return 1LL * elf * 11;
}

LL nrPresents(int x) {
  LL cnt = 0;
  for (int i = 1; i * i <= x; ++i) {
    cnt += presentsTo(x, i);
    cnt += presentsTo(x, x / i);
  }
  return cnt;
}

int main() {
  freopen("in", "r", stdin);
  LL inp = 29000000;
  for (int i = 0;; ++i) {
    if (nrPresents(i) > inp) {
      printf("%d\n", i);
      break;
    }
  }
  return 0;
}
