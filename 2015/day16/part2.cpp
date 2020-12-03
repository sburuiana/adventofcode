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
char buf[MAXBUF], a[MAXBUF], b[MAXBUF], c[MAXBUF];

struct cookie {
  char name[100];
  int c, d, f, t, ca;
};

bool okcmp(int actual, int data, string which) {
  if (which == "trees:" || which == "cats:")
    return actual > data;
  if (which == "pomeranians:" || which == "goldfish:")
    return actual < data;
  return actual == data;
}

int main() {
  freopen("in", "r", stdin);
  map<string, int> d;
  d["children:"] = 3;
  d["cats:"] = 7;
  d["samoyeds:"] = 2;
  d["pomeranians:"] = 3;
  d["akitas:"] = 0;
  d["vizslas:"] = 0;
  d["goldfish:"] = 5;
  d["trees:"] = 3;
  d["cars:"] = 2;
  d["perfumes:"] = 1;
  int nr, xa, xb, xc;
  while (scanf("%s %d: %s %d, %s %d, %s %d", buf, &nr, a, &xa, b, &xb, c, &xc) != EOF) {
    bool flag = true;
    if (!okcmp(xa, d[string(a)], string(a))) flag = false;
    if (!okcmp(xb, d[string(b)], string(b))) flag = false;
    if (!okcmp(xc, d[string(c)], string(c))) flag = false;
    if (flag) printf("%d\n", nr);
  }
  return 0;
}
