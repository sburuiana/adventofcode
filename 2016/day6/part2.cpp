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

int main() {
  freopen("in", "r", stdin);
  vector<string> lines = getAllLines();
  string s = lines[0];
  vector< map<char, int> > f;
  f.resize(s.size());
  for (auto& it : lines)
    for (int i = 0; i < (int)it.size(); ++i)
      f[i][it[i]]++;
  for (int i = 0; i < (int)s.size(); ++i) {
    pair<int, char> best = mp(INT_MAX, 'a');
    for (auto& it : f[i])
      best = min(best, mp(it.second, it.first));
    s[i] = best.second;
  }
  printf("%s\n", s.c_str());
      
  return 0;
}
