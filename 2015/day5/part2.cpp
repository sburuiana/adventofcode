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
bool isVowel[255];

bool isNice(const char* s) {
  map< pair<char, char>, const char* > pos;
  bool dpair = false;
  bool dletter = false;
  for (const char* i = s; *i; ++i) {
    SKIP(i <= s);
    pair<char, char> key = mp(*(i - 1), *i);
    if (pos.count(key)) {
      if (i - pos[key] >= 2) dpair = true;
    }
    else pos[key] = i;
    SKIP(i <= s + 1);
    if (*(i - 2) == *i) dletter = true;
  }
  return dpair && dletter;
}

int main() {
  freopen("in", "r", stdin);
  isVowel['a'] = isVowel['e'] = isVowel['i'] = isVowel['o'] = isVowel['u'] = true;
  int s = 0;
  while (scanf("%s", buf) != EOF) {
    if (isNice(buf)) ++s;
  }
  printf("%d\n", s);
  return 0;
}
