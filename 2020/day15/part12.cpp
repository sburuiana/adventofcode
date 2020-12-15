#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long LL;
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

int main() {
  freopen("in", "r", stdin);
  vector<int> v =
    tokenize("2,0,1,9,5,19", ',');
    //tokenize("0,3,6", ',');
  map<int, vector<int> > m;
  for (int i = 0; i < (int)v.size(); ++i)
    m[v[i]].push_back(i);
  int lst = v.back();
  for (int i = v.size(); i < 30000000; ++i) {
    if (m[lst].size() < 2) {
      lst = 0;
    }
    else {
      lst = m[lst].back() - m[lst][m[lst].size() - 2];
    }
    m[lst].push_back(i);
    if(i + 1 == 2020)
      printf("Part 1: %d\n", lst);
  }
  printf("Part 2: %d\n", lst);
  return 0;
}
