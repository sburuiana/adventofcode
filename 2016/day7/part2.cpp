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

bool isaba(string& l, int i) {
  CHECK(i >= 2);
  CHECK(l[i] == l[i - 2]);
  CHECK(isalpha(l[i - 1]) && isalpha(l[i]));
  CHECK(l[i - 1] != l[i]);
  return true;
}

int main() {
  freopen("in", "r", stdin);
  vector<string> lines = getAllLines();
  int s = 0;
  for (auto& l : lines) {
    set<string> aba, bab;
    int n = (int)l.size();
    int bracket = 0;
    for (int i = 0; i < n; ++i) {
      if (isaba(l, i)) {
        if (bracket <= 0) aba.insert(l.substr(i - 2, 3));
        else bab.insert(l.substr(i - 2, 3));
      }
      if (l[i] == '[') ++bracket;
      else if (l[i] == ']') --bracket;
    }
    for (const auto& it : aba) {
      string coresp = it;
      coresp[0] = coresp[2] = it[1];
      coresp[1] = it[0];
      if (bab.count(coresp)) {
        ++s;
        break;
      }
    }
  }
  printf("%d\n", s);
  return 0;
}
