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

LL &getParam(LL opIdx, LL argIdx, map<LL, LL> &P, LL &relBase) {
  LL mode = P[opIdx] / 100;
  for (LL i = 0; i < argIdx - 1; mode /= 10, ++i);
  mode %= 10;
  argIdx += opIdx;
  if (mode == 0) return P[P[argIdx]];
  else if (mode == 1) return P[argIdx];
  else if (mode == 2) return P[P[argIdx] + relBase];
}

#define TERNARY_OPERATOR(op) getParam(eip, 3, P, rb) = (LL)(getParam(eip, 1, P, rb) op getParam(eip, 2, P, rb)); eip += 4;

pair<vector<LL>, bool> runLLcode(map<LL, LL> &P, queue<LL> &inputs, LL &eip, LL &rb) {
  vector<LL> outputs;
  while (eip < (LL)P.size()) {
    switch (P[eip] % 100) {
    case 99:
      eip = LLONG_MAX; break;
    case 1:
      TERNARY_OPERATOR(+); break;
    case 2:
      TERNARY_OPERATOR(*); break;
    case 3: {
      if (inputs.empty()) return mp(outputs, false);
      getParam(eip, 1, P, rb) = inputs.front();
      inputs.pop();
      eip += 2;
      break;
    }
    case 4:
      //prLLf("%d\n", getParam(eip, 1, P));
      outputs.push_back(getParam(eip, 1, P, rb));
      eip += 2;
      break;
    case 5:
      eip = getParam(eip, 1, P, rb) ? getParam(eip, 2, P, rb) : (eip + 3);
      break;
    case 6:
      eip = getParam(eip, 1, P, rb) ? (eip + 3) : getParam(eip, 2, P, rb);
      break;
    case 7:
      TERNARY_OPERATOR(<);
      break;
    case 8:
      TERNARY_OPERATOR(== );
      break;
    case 9:
      rb += getParam(eip, 1, P, rb);
      eip += 2;
      break;
    default:
      break;
    }
  }
  return mp(outputs, true);
}

void readIntcode(string s, map<LL, LL> &P) {
  replace(s.begin(), s.end(), ',', ' ');
  vector<LL> PP;
  LL x, aux;
  for (LL offset = 0; sscanf(s.c_str() + offset, "%I64d%lln", &x, &aux) >= 0; offset += aux, PP.push_back(x));
  for (LL i = 0; i < (LL)PP.size(); ++i)
    P[i] = PP[i];
}

char buffer[2000];

/*
PART 1:
NOT J J
AND A J
AND B J
AND C J
NOT J J
AND D J
WALK
*/

/*
PART 2:
NOT J J
AND A J
AND B J
AND C J
NOT J J
AND D J
OR E T
OR H T
AND T J
RUN
*/

int main() {
  //freopen("fis.in", "r", stdin);
  ifstream fin("fis.in");
  string s;
  fin >> s;
  map<LL, LL> P;
  readIntcode(s, P);
  
  queue<LL> Q;
  //Q.push(2);
  LL eip = 0, rb = 0;
  while (1) {
    auto res = runLLcode(P, Q, eip, rb);
    for (const auto &it : res.first) {
      if(it < 255) putchar((char)it);
      else printf("%I64d\n", it);
      fflush(stdout);
    }
    if (res.second) break;
    gets_s(buffer, sizeof buffer);
    for (char *i = buffer; *i; ++i)
      Q.push((LL)(*i));
    Q.push((LL)('\n'));
  }
  return 0;
}
