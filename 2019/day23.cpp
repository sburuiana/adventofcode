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

struct prog {
  map<LL, LL> P;
  queue<LL> Q;
  LL eip, rb;
  prog() {
  }
  prog(map<LL, LL> p, queue<LL> q, LL e, LL r) : P(p), Q(q), eip(e), rb(r) {}
};

const int PROGS = 50;

int main() {
  ifstream fin("fis.in");
  string s;
  fin >> s;
  map<LL, LL> P;
  readIntcode(s, P);
  LL eip = 0, rb = 0;
  queue<LL> Q;

  vector<prog> v;
  for (int i = 0; i < PROGS; ++i) {
    v.push_back(prog(P, Q, eip, rb));
    v.back().Q.push(i);
  }

  map<LL, queue<pll> > packetQueue;

  bool flag = true;
  pll NATpacket = mp(-1, -1);
  pll lastZeroPacket = mp(-10, -10);
  while (1) {
    flag = false;
    for (int i = 0; i < PROGS; ++i) {
      while (!packetQueue[i].empty()) {
        pll t = packetQueue[i].front();
        packetQueue[i].pop();
        v[i].Q.push(t.first); v[i].Q.push(t.second);
        flag = true;
      }
      if (v[i].Q.empty()) v[i].Q.push(-1);
      auto res = runLLcode(v[i].P, v[i].Q, v[i].eip, v[i].rb);
      assert(res.first.size() % 3 == 0);
      for (int i = 0; i < (int)res.first.size(); i += 3) {
        flag = true;
        if (res.first[i] == 255) {
          NATpacket = mp(res.first[i + 1], res.first[i + 2]);
          //printf("%I64d %I64d\n", res.first[i + 1], res.first[i + 2]);
          continue;
        }
        packetQueue[res.first[i]].push(mp(res.first[i + 1], res.first[i + 2]));
      }
      SKIP(res.second);
    }
    if (!flag) {
      packetQueue[0].push(NATpacket);
      if (lastZeroPacket.second == NATpacket.second) {
        cout << lastZeroPacket.second << endl;
        return 0;
      }
      lastZeroPacket = NATpacket;
    }
  }

  //auto res = runLLcode(P, Q, eip, rb);
  return 0;
}
