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

map<int, int> botval1, botval2;
map<int, pii> botgives;
map<int, vector<int> > getsfrom;
set<int> viz;

void addVal(int bot, int val) {
  if (botval1.count(bot)) botval2[bot] = val;
  else botval1[bot] = val;
}

char buf[100];

void DFS(int target) {
  CHECKRET(!viz.count(target), void());
  viz.insert(target);
  for (const auto& it : getsfrom[target])
    DFS(it);
  if (botgives.count(target) == 0) return;
  CHECKRET(botgives.count(target), void());
  assert(botval1.count(target) && botval2.count(target));
  int val1 = botval1[target], val2 = botval2[target];
  if (val1 > val2) swap(val1, val2);
  if (val1 == 17 && val2 == 61)
    printf("Part 1: %d\n", target - 1);
  addVal(botgives[target].first, val1);
  addVal(botgives[target].second, val2);
}

int main() {
  freopen("in", "r", stdin);
  for (auto& line : getAllLines()) {
    if (line[0] == 'v') {
      int a, b;
      sscanf(line.c_str(), "value %d goes to bot %d", &a, &b);
      ++b;
      addVal(b, a);
    }
    else {
      int bot, val1, val2;
      char which1[100], which2[100];
      sscanf(line.c_str(), "bot %d gives low to %s %d and high to %s %d", &bot, which1, &val1, which2, &val2);
      ++bot;
      ++val1, ++val2;
      if (which1[0] == 'o') val1 = -val1;
      if (which2[0] == 'o') val2 = -val2;
      botgives[bot] = pii(val1, val2);
      getsfrom[val1].push_back(bot);
      getsfrom[val2].push_back(bot);
    }
  }
  for (const auto& it : getsfrom)
    DFS(it.first);
  printf("Part 2: %I64d\n", 1LL * botval1[-1] * botval1[-2] * botval1[-3]);
  return 0;
}
