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

int main() {
  freopen("in", "r", stdin);
  lines = getAllLines();
  string p1 = "13,25,18,6,42,8,37,27,44,38,10,28,50,5,16,47,30,29,39,21,2,4,12,35,32";
  string p2 = "20,14,46,34,7,26,15,43,36,49,11,23,31,48,1,19,45,22,24,40,41,17,33,9,3";
  dq p1d = tokenize(p1, ',');
  dq p2d = tokenize(p2, ',');
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
  dq* wr;
  if (p1d.empty()) wr = &p2d;
  else wr = &p1d;
  int scor = 0;
  int v = 1;
  for (auto it = wr->rbegin(); it != wr->rend(); ++it, ++v)
    scor += (*it) * v;
  printf("%d\n", scor);
  return 0;
}
