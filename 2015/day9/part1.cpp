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
  set<string> allCities;
  map< pair<string, string>, int > dst;
  int d;
  while (scanf("%s to %s = %d", a, b, &d) != EOF) {
    dst[mp(a, b)] = dst[mp(b, a)] = d;
    allCities.insert(a);
    allCities.insert(b);
  }
  vector<string> cities;
  for (const auto& it : allCities) cities.push_back(it);
  int best = INT_MAX;
  do {
    int cand = 0;
    for (int i = 1; i < (int)cities.size() && cand != INT_MAX; ++i) {
      string a = cities[i - 1], b = cities[i];
      if (dst.count(mp(a, b)) == 0) cand = INT_MAX;
      else cand += dst[mp(a, b)];
    }
    best = min(best, cand);
  } while (next_permutation(cities.begin(), cities.end()));
  printf("%d\n", best);
  return 0;
}
