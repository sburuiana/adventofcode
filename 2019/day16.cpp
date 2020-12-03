#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
//#define int LL
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

typedef pair<int, string> pis;

vector< pis > tokenize(string s, char by1, char by2 = ' ', char by3 = ' ') {
  replace(s.begin(), s.end(), by1, ' ');
  replace(s.begin(), s.end(), by2, ' ');
  replace(s.begin(), s.end(), by3, ' ');
  int x, aux;
  vector< pis > P;
  char buffer[200];
  for (int offset = 0; sscanf(s.c_str() + offset, "%d%s%n", &x, buffer, &aux) >= 0; ) {
    offset += aux, P.push_back(mp(x, string(buffer)));
  }
  return P;
}

int toInt(string s) {
  int x;
  sscanf(s.c_str(), "%d", &x);
  return x;
}

const int pat[] = { 0, 1, 0, -1 };

inline int sft(int l, int r, vector<int> &ps) {
  if (r >= ps.size()) r = (int)ps.size() - 1;
  if (l > r) return 0;
  int ans = ps[r];
  if (l > 0) ans -= ps[l - 1];
  return ans;
}

#define PART2

uint32_t main() {
  freopen("fis.in", "r", stdin);
  //freopen("fis.out", "w", stdout);
  vector<string> lines = getAllLines();
  string s = lines[0];
#ifdef PART2
  s = "";
  for (int i = 0; i < 10000; ++i)
    s += lines[0];
  cout << "Done build\n";
  int pos = toInt(s.substr(0, 7));
#endif
  //s = "12345678";  

  vector<int> partialSums;
  string nou;
  for (int p = 0; p < 100; ++p) {
    partialSums.clear();
    for (const auto &it : s) {
      int s = it - '0';
      if (!partialSums.empty()) s += partialSums.back();
      partialSums.push_back(s);
    }
    nou.clear();
    for (int pos = 0; pos < (int)s.size(); ++pos) {
      //cout << pos << " ";
      int suma = 0;
      for (int i = 0, pi = 0, pdone = 1; i < (int)s.size();) {

        if (pdone >= pos + 1) {
          pi = (pi + 1) % 4;
          pdone = 0;
        }

        int left = (pos + 1) - pdone;
        int epos = i + left - 1;

        suma += sft(i, epos, partialSums) * pat[pi];

        i += left;
        pi = (pi + 1) % 4;
        pdone = 0;
      }
      nou.push_back(abs(suma) % 10 + '0');
    }
    //cout << nou << endl;
    s.swap(nou);
    cout << "Done " << p << endl;
  }
#ifndef PART2
  cout << s.substr(0, 8) << endl;
#else
  cout << s.substr(pos, 8) << endl;
#endif
  cout << "Done in " << 1.0 * clock() / CLOCKS_PER_SEC << endl;
  return 0;
}
