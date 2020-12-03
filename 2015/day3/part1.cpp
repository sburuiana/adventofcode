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

char buf[2000000];

int main() {
  freopen("in", "r", stdin);
  scanf("%s", buf);
  pii x = mp(0, 0);
  map<pii, int> M;
  M[x] = 1;
  for (char* i = buf; *i; ++i) {
    switch (*i) {
    case '<':
      x.first -= 1;
      break;
    case '>':
      x.first += 1;
      break;
    case '^':
      x.second -= 1;
      break;
    case 'v':
      x.second += 1;
      break;
    }
    M[x] += 1;
  }
  printf("%d\n", (int)M.size());
  return 0;
}
