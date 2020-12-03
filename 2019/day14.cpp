#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define int LL
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

typedef pair<int, string> pis;

vector< pis > tokenize(string s, char by1, char by2, char by3) {
  replace(s.begin(), s.end(), by1, ' ');
  replace(s.begin(), s.end(), by2, ' ');
  replace(s.begin(), s.end(), by3, ' ');
  int x, aux;
  vector< pis > P;
  char buffer[200];
  for (int offset = 0; sscanf(s.c_str() + offset, "%I64d%s%I64n", &x, buffer, &aux) >= 0; ) {
    offset += aux, P.push_back(mp(x, string(buffer)));
  }
  return P;
}

int toInt(string s) {
  int x;
  sscanf(s.c_str(), "%I64d", &x);
  return x;
}

map<string, pair<int, vector<pis> > > M;

inline int mceil(int a, int b) {
  assert(b != 0);
  int rez = a / b;
  if (a % b != 0) ++rez;
  return rez;
}

int costToGet(int howMuch) {
  map<string, int> req;
  for (const auto &it : M["FUEL"].second) {
    req[it.second] = it.first * howMuch;
  }
  bool flag = true;
  while (flag) {
    flag = false;
    for (const auto &it : req) {
      const string &name = it.first;
      int amount = it.second;
      SKIP(amount <= 0);
      SKIP(name == "ORE");
      int reactions = mceil(amount, M[name].first);
      for (const auto &it2 : M[name].second)
        req[it2.second] += it2.first * reactions;
      req[name] -= reactions * M[name].first;
      flag = true;
      //break;
    }
  }
  return req["ORE"];
}

LL binSrch() {
  LL ore = 1000000000000LL;
  LL found = ore / costToGet(1);
  LL l = found + 1, r = ore;
  while (l <= r) {
    LL mid = l + (r - l) / 2;
    if (costToGet(mid) <= ore) {
      found = mid;
      l = mid + 1;
    }
    else r = mid - 1;
  }
  return found;
}

uint32_t main() {
  freopen("fis.in", "r", stdin);
  vector<string> lines = getAllLines();
  for (const auto &line : lines) {
    vector<pis> caca = tokenize(line, ',', '>', '=');
    pis rez = caca.back();
    caca.pop_back();
    assert(!M.count(rez.second));
    M[rez.second] = mp(rez.first, caca);
  }
  printf("%I64d\n", costToGet(1));
  printf("%I64d\n", binSrch());
  return 0;
}
