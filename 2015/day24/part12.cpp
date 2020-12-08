#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define mp make_pair
#define CHECK(x) if(!(x)) return false;
#define CHECKRET(x, y) if(!(x)) return (y);
#define SKIP(x) if((x)) continue;
typedef pair<int, int> pii;

vector<int> v, g;
int gsz[10];
int N;
int tars;
int s[10];
int GRPS = 4; // <---- change to 3 for part 1

LL mult(LL a, LL b) {
  if (a > LLONG_MAX / b) return LLONG_MAX;
  return 1LL * a * b;
}

bool cmp(int x, int y) {
  return x < y;
}

pair<int, LL> bkt(int lvl) {
  pair<int, LL> best = mp(INT_MAX, 0);
  if (lvl == N) {
    int n = 0;
    LL qe = 1;
    for (int i = 0; i < N; ++i) {
      SKIP(g[i] != 0);
      ++n;
      qe = mult(qe, v[i]);
    }
    if (s[0] == s[1] && s[1] == s[2]) return mp(n, qe);
    return best;
  }
  for (g[lvl] = 0; g[lvl] < GRPS; ++g[lvl]) {
    s[g[lvl]] += v[lvl];
    ++gsz[g[lvl]];
    if(
      (s[g[lvl]] <= tars) &&
      !(g[lvl] == 0 && gsz[g[lvl]] * GRPS > N)
      )
      best = min(best, bkt(lvl + 1));
    s[g[lvl]] -= v[lvl];
    --gsz[g[lvl]];
    if (g[lvl] > 0 && gsz[g[lvl]] == 0) break;
  }
  return best;
}

int main() {
  freopen("in", "r", stdin);
  int x;
  while (scanf("%d", &x) != EOF) {
    v.push_back(x);
    tars += x;
  }
  sort(v.rbegin(), v.rend());
  N = v.size();
  g.resize(N);
  tars /= GRPS;
  auto res = bkt(0);
  printf("%I64d\n", res.second);
  return 0;
}
