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

string inc(string s) {
  for (auto it = s.rbegin(); it != s.rend(); ++it) {
    *it += 1;
    if ((*it) > 'z') {
      *it = 'a';
    }
    else return s;
  }
  s = "a" + s;
  return s;
}

bool ok(string s) {
  bool flag = false;
  map< char, string::iterator > pos;
  int nrp = 0;
  for (auto it = s.begin(); it != s.end(); ++it) {
    CHECK(*it != 'i' && *it != 'o' && *it != 'l');
    if (distance(s.begin(), it) >= 2) {
      char x = *(it - 2), y = *(it - 1), z = *it;
      if (y == x + 1 && z == y + 1) flag = true;
    }
    SKIP(it == s.begin());
    SKIP(*it != *(it - 1));
    if (pos.count(*it) && it - pos[*it] < 2);
    else ++nrp, pos[*it] = it;
  }
  return flag && nrp >= 2;
}

int main() {
  freopen("in", "r", stdin);
  string s = "hepxcrrq";
  while (!ok(s)) s = inc(s);
  cout << "Part 1 " << s << endl;
  s = inc(s);
  while (!ok(s)) s = inc(s);
  cout << "Part 2 " << s << endl;
  return 0;
}
