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

struct cookie {
  char name[100];
  int c, d, f, t, ca;
};

int main() {
  freopen("in", "r", stdin);
  cookie c;
  vector<cookie> v;
  while (scanf("%s capacity %d, durability %d, flavor %d, texture %d, calories %d", &c.name, &c.c, &c.d, &c.f, &c.t, &c.ca) != EOF) {
    cookie cc;
    memcpy(&cc, &c, sizeof c);
    v.push_back(cc);
  }
  LL best = 0;
  int UPTO = 100;
  for (int i = 0; i < UPTO; ++i)
    for (int j = 0; j < UPTO; ++j)
      for (int k = 0; k < UPTO; ++k)
        for (int l = 0; l < UPTO; ++l) {
          SKIP(i + j + k + l != UPTO);
          int c = v[0].c * i + v[1].c * j + v[2].c * k + v[3].c * l;
          if (c < 0) c = 0;
          int f = v[0].f * i + v[1].f * j + v[2].f * k + v[3].f * l;
          if (f < 0) f = 0;
          int d = v[0].d * i + v[1].d * j + v[2].d * k + v[3].d * l;
          if (d < 0) d = 0;
          int t = v[0].t * i + v[1].t * j + v[2].t * k + v[3].t * l;
          if (t < 0) t = 0;
          int ca = v[0].ca * i + v[1].ca * j + v[2].ca * k + v[3].ca * l;
          LL cand = 1LL * c * f * d * t;
          if(ca == 500) best = max(best, cand);
        }
  printf("%I64d\n", best);
  return 0;
}
