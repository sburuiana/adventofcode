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
  while (scanf("%s would %s %d happiness units by sitting next to %s.", a, buf, &d, b) != EOF) {
    if (buf[0] == 'l') d = -d;
    b[strlen(b) - 1] = 0;
    dst[mp(a, b)] = d;
    allCities.insert(a);
    allCities.insert(b);
  }
  vector<string> cities;
  for (const auto& it : allCities) cities.push_back(it);
  int best = 0;
  do {
    int cand = 0;
    for (int i = 0; i < (int)cities.size() && cand != INT_MAX; ++i) {
      string a = cities[i], b = cities[(i + 1) % cities.size()];
      cand += dst[mp(a, b)] + dst[mp(b, a)];
    }
    best = max(best, cand);
  } while (next_permutation(cities.begin(), cities.end()));
  printf("%d\n", best);
  return 0;
}
