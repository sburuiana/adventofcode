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

const int MAXBUF = 2000;
char buf[MAXBUF], a[MAXBUF], b[MAXBUF];

int main() {
  freopen("in", "r", stdin);
  int T = 2503;
  int spd, secs, rest;
  LL best = 0;
  while (scanf("%s can fly %d km/s for %d seconds, but then must rest for %d seconds.", buf, &spd, &secs, &rest) != EOF) {
    LL res = 0;
    int fullp = T / (secs + rest);
    res += 1LL * fullp * spd * secs;
    int remaining = T - fullp * (secs + rest);
    res += 1LL * min(remaining, secs) * spd;
    best = max(best, res);
  }
  printf("%I64d\n", best);
  return 0;
}
