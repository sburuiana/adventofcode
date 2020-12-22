#include <bits/stdc++.h>
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

vector<string> lines;

pair<int, pair<dq, dq> > playGame(pair<dq, dq> p12);
pair< int, pair<dq, dq> > playRound(pair<dq, dq> p12, set< pair<dq, dq> > &viz);

pair< int, pair<dq, dq> > playRound(pair<dq, dq> p12, set< pair<dq, dq> > &viz) {
  if (viz.count(p12)) return mp(1, p12);
  viz.insert(p12);
  if (p12.first.empty()) return mp(2, p12);
  if (p12.second.empty()) return mp(1, p12);
  int top1 = p12.first.front();
  int top2 = p12.second.front();
  p12.first.pop_front();
  p12.second.pop_front();
  int w = 1;
  if ((int)p12.first.size() < top1 || (int)p12.second.size() < top2) {
    w = (top1 > top2) ? 1 : 2;
  }
  else {
    pair<dq, dq> nxt = p12;
    while ((int)nxt.first.size() > top1) nxt.first.pop_back();
    while ((int)nxt.second.size() > top2) nxt.second.pop_back();
    w = playGame(nxt).first;
  }
  if (w == 1) {
    p12.first.push_back(top1);
    p12.first.push_back(top2);
  }
  else {
    p12.second.push_back(top2);
    p12.second.push_back(top1);
  }
  return mp(-1, p12);
}

pair<int, pair<dq, dq> > playGame(pair<dq, dq> p12) {
  set< pair<dq, dq> > viz;
  while (1) {
    auto res = playRound(p12, viz);
    p12 = res.second;
    if (res.first >= 0) return res;
  }
}

int main() {
  freopen("in", "r", stdin);
  lines = getAllLines();
  string p1 = //"9,2,6,3,1";
    "13,25,18,6,42,8,37,27,44,38,10,28,50,5,16,47,30,29,39,21,2,4,12,35,32";
  string p2 = //"5,8,4,7,10";
    "20,14,46,34,7,26,15,43,36,49,11,23,31,48,1,19,45,22,24,40,41,17,33,9,3";
  dq p1d = tokenize(p1, ',');
  dq p2d = tokenize(p2, ',');
  /*
  while (!p1d.empty() && !p2d.empty()) {
    int c1 = p1d.front(),
      c2 = p2d.front();
    p1d.pop_front(), p2d.pop_front();
    if (c1 > c2) {
      p1d.push_back(c1);
      p1d.push_back(c2);
    }
    else {
      p2d.push_back(c2);
      p2d.push_back(c1);
    }
  }
  */
  auto res = playGame(mp(p1d, p2d));
  dq* wr;
  if (res.first == 1) wr = &res.second.first;
  else wr = &res.second.second;
  int scor = 0;
  int v = 1;
  for (auto it = wr->rbegin(); it != wr->rend(); ++it, ++v)
    scor += (*it) * v;
  printf("%d\n", scor);
  return 0;
}
