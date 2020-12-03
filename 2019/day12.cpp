#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define mp make_pair
#define CHECK(x) if(!(x)) return false;
#define CHECKRET(x, y) if(!(x)) return (y);
#define SKIP(x) if((x)) continue;
typedef pair<LL, LL> pii;

vector<string> getAllLines() {
  vector<string> v;
  string s;
  while (getline(cin, s)) {
    SKIP(s.size() <= 0);
    v.push_back(s);
  }
  return v;
}
LL toInt(const string &s) {
  LL x;
  sscanf(s.c_str(), "%I64d", &x);
  return x;
}
vector<LL> tokenize(string &s, char by) {
  vector<LL> v;
  return v;
}

struct punct {
  vector<LL> d;
  punct() {
    d.resize(3);
  }
  punct(LL x, LL y, LL z) {
    d.resize(3);
    d[0] = x, d[1] = y, d[2] = z;
  }
  LL energy() {
    return abs(d[0]) + abs(d[1]) + abs(d[2]);
  }
  const bool operator<(const punct &other) const {
    if (d[0] != other.d[0]) return d[0] < other.d[0];
    if (d[1] != other.d[1]) return d[1] < other.d[1];
    if (d[2] != other.d[2]) return d[2] < other.d[2];
    return false;
  }
};

LL cmp(LL a, LL b) {
  if (a == b) return 0;
  if (a < b) return -1;
  return 1;
}

set< vector< pair<punct, punct> > > allStates;

void gravity(vector< pair<punct, punct> > &v) {
  LL n = v.size();
  for (LL i = 0; i < n; ++i)
    for (LL j = 0; j < n; ++j) {
      SKIP(i == j);
      v[i].second.d[0] -= cmp(v[i].first.d[0], v[j].first.d[0]);
      v[i].second.d[1] -= cmp(v[i].first.d[1], v[j].first.d[1]);
      v[i].second.d[2] -= cmp(v[i].first.d[2], v[j].first.d[2]);
    }
}

void position(vector< pair<punct, punct> > &v) {
  LL n = v.size();
  for (LL i = 0; i < n; ++i) {
    v[i].first.d[0] += v[i].second.d[0];
    v[i].first.d[1] += v[i].second.d[1];
    v[i].first.d[2] += v[i].second.d[2];
  }
}

LL lcm(LL a, LL b) {
  return a * b / gcd(a, b);
}

int main() {
  freopen("fis.in", "r", stdin);
  vector<string> lines = getAllLines();
  vector< pair<punct, punct> > v;
  for (const auto &it : lines) {
    punct p;
    sscanf(it.c_str(), "<x=%I64d, y=%I64d, z=%I64d>", &p.d[0], &p.d[1], &p.d[2]);
    v.push_back(mp(p, punct(0, 0, 0)));
  }
  /*
  LL s = 0;
  for (auto &it : v) {
    s += it.first.energy() * it.second.energy();
  }
  printf("%d\n", s);
  */
  LL res = 1;
  for (int dim = 0; dim < 3; ++dim) {
    vector< pair<punct, punct> > w = v;
    for (int d = 0; d < 3; ++d) {
      SKIP(d == dim);
      for (auto &it : w)
        it.first.d[d] = 0;
    }
    allStates.insert(w);
    for (LL steps = 1; ; ++steps) {
      gravity(w);
      position(w);
      if (allStates.count(w)) {
        printf("Found same state in %I64d steps\n", steps);
        res = lcm(res, steps);
        break;
      }
    }
  }
  printf("%I64d\n", res);
  return 0;
}
