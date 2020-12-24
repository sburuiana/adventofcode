#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
typedef long long LL;
#define mp make_pair
#define CHECK(x) if(!(x)) return false;
#define CHECKRET(x, y) if(!(x)) return (y);
#define SKIP(x) if((x)) continue;
typedef pair<int, int> pii;
typedef deque<int> dq;

vector<string> getAllLines() {
  vector<string> v;
  string s;
  while (getline(cin, s)) {
    SKIP(s.size() <= 0);
    v.push_back(s);
  }
  return v;
}

dq tokenize(string s, char by) {
  replace(s.begin(), s.end(), by, ' ');
  int x, aux;
  dq P;
  for (int offset = 0; sscanf(s.c_str() + offset, "%d%n", &x, &aux) >= 0; offset += aux, P.push_back(x));
  return P;
}

int toInt(string s) {
  int x;
  sscanf(s.c_str(), "%d", &x);
  return x;
}

vector< pair<int, int> > vecini;

void makengh() {
  vecini.reserve(6);

  vecini.push_back(make_pair(0, -1)); //nw 0
  vecini.push_back(make_pair(-1, 0)); //w  1
  vecini.push_back(make_pair(-1, 1)); //sw 2
  vecini.push_back(make_pair(0, 1)); //se  3
  vecini.push_back(make_pair(1, 0)); //e   4
  vecini.push_back(make_pair(1, -1)); //ne 5
}

int main() {
  freopen("in", "r", stdin);
  vector<string> lines = getAllLines();
  makengh();
  set<pii> flipped;
  for (string& s : lines) {
    pii cur = mp(0, 0);
    for (int i = 0; i < (int)s.size(); ++i) {
      int di = 0;
      if (s[i] == 'e') di = 4;
      else if (s[i] == 's') {
        if (s[i + 1] == 'e') di = 3;
        else di = 2;
        ++i;
      }
      else if (s[i] == 'w') di = 1;
      else {
        if (s[i + 1] == 'e') di = 5;
        else di = 0;
        ++i;
      }
      cur.first += vecini[di].first;
      cur.second += vecini[di].second;
    }
    if (flipped.count(cur)) flipped.erase(cur);
    else flipped.insert(cur);
  }
  printf("Part 1 %d\n", (int)flipped.size());
  for (int _ = 0; _ < 100; ++_) {
    set<pii> nflipped;
    for (auto& it : flipped)
      for (int vi = 0; vi < 7; ++vi) {
        pii delta = mp(0, 0);
        if (vi < 6) delta = vecini[vi];
        int cnt = 0;
        pii sq = mp(it.first + delta.first, it.second + delta.second);
        for (int i = 0; i < 6; ++i) {
          pii nsq = mp(sq.first + vecini[i].first, sq.second + vecini[i].second);
          if (flipped.count(nsq)) ++cnt;
        }
        if (flipped.count(sq) && !(cnt == 0 || cnt > 2)) nflipped.insert(sq);
        if (!flipped.count(sq) && cnt == 2) nflipped.insert(sq);
      }
    flipped.swap(nflipped);
  }
  printf("Part 2 %d\n", (int)flipped.size());
  return 0;
}