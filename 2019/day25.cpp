#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define mp make_pair
#define CHECK(x) if(!(x)) return false;
#define CHECKRET(x, y) if(!(x)) return (y);
#define SKIP(x) if((x)) continue;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;

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

pair<vector<LL>, bool> runLLcode(map<LL, LL> &P, deque<LL> &inputs, LL &eip, LL &rb) {
  vector<LL> outputs;
  while (1) {
    switch (P[eip] % 100) {
    case 99:
      eip = LLONG_MAX;
      return mp(outputs, true);
      break;
    case 1:
      TERNARY_OPERATOR(+); break;
    case 2:
      TERNARY_OPERATOR(*); break;
    case 3: {
      if (inputs.empty()) return mp(outputs, false);
      getParam(eip, 1, P, rb) = inputs.front();
      inputs.pop_front();
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
      printf("Invalid operator %I64d at %I64d\n", P[eip], eip);
      return mp(outputs, true);
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

struct prog {
  map<LL, LL> P;
  deque<LL> Q;
  LL eip, rb;
  prog() : P(), Q(), eip(0), rb(0) {}
  prog(map<LL, LL> p) : P(p), Q(), eip(0), rb(0) {}
  prog(map<LL, LL> p, deque<LL> q, LL e, LL r) : P(p), Q(q), eip(e), rb(r) {}
  pair<vector<LL>, bool> run() {
    return runLLcode(P, Q, eip, rb);
  }
  void feedInput(LL x) {
    Q.push_back(x);
  }
  void feedInputS(string s) {
    for(const auto &it : s)
      Q.push_back(it);
    Q.push_back('\n');
  }
  prog clone() {
    return prog(P, Q, eip, rb);
  }
  void serialize(ofstream &fout) {
    fout << eip << " " << rb << endl;
    fout << Q.size() << " ";
    for (const auto &it : Q) fout << it << " " << endl;
    fout << P.size() << " ";
    for (const auto &it : P) fout << it.first << " " << it.second << " ";
    fout << endl;
  }
  void loadFrom(ifstream &fin) {
    Q.clear();
    fin >> eip >> rb;
    int n;
    fin >> n;
    LL a, b;
    for (int i = 0; i < n; ++i) {
      fin >> a;
      Q.push_back(a);
    }
    P.clear();
    fin >> n;
    for (int i = 0; i < n; ++i) {
      fin >> a >> b;
      P[a] = b;
    }
  }
};

int main() {
  ifstream fin("fis.in");
  string s;
  fin >> s;
  prog P;
  readIntcode(s, P.P);
  while (1) {
    auto res = P.run();
    for (const auto &it : res.first) {
      if(it < 255)
        putchar((char)it);
      else cout << it << endl;
    }
    if (res.second) {
      cout << "!! Terminated !!" << endl;
      break;
    }
    string s;
    while (1) {
      getline(cin, s);
      if (s == "save") {
        ofstream fout("fis.out");
        P.serialize(fout);
        fout.close();
        continue;
      }
      else if (s == "load") {
        ifstream fout("fis.out");
        P.loadFrom(fout);
        fout.close();
        continue;
      }
      break;
    }
    P.feedInputS(s);
  }
  return 0;
}
