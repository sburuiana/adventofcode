#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define mp make_pair
#define CHECK(x) if(!(x)) return false;
#define CHECKRET(x, y) if(!(x)) return (y);
#define SKIP(x) if((x)) continue;
typedef pair<LL, LL> pii;

LL &getParam(LL opIdx, LL argIdx, vector<LL> &P, LL relBase) {
  LL mode = P[opIdx] / 100;
  for (LL i = 0; i < argIdx - 1; mode /= 10, ++i);
  mode %= 10;
  argIdx += opIdx;
  if (mode == 0) return P[P[argIdx]];
  else if(mode == 1) return P[argIdx];
  else if (mode == 2) return P[P[argIdx] + relBase];
}

#define TERNARY_OPERATOR(op) getParam(eip, 3, P, rb) = (LL)(getParam(eip, 1, P, rb) op getParam(eip, 2, P, rb)); eip += 4;

pair<vector<LL>, pii> runLLcode(vector<LL> &P, deque<LL> &inputs, LL eip = 0) {
  LL rb = 0;
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
      if (inputs.empty()) return mp(outputs, mp(eip, 0));
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
      TERNARY_OPERATOR(< );
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
  return mp(outputs, mp(eip, 1));
}

int main() {
  freopen("fis.in", "r", stdin);
  string s;
  cin >> s;
  replace(s.begin(), s.end(), ',', ' ');
  vector<LL> P;
  LL x, aux;
  for (LL offset = 0; sscanf(s.c_str() + offset, "%I64d%lln", &x, &aux) >= 0; offset += aux, P.push_back(x));
  P.resize(1000000000);
  deque<LL> D;
  D.push_back(2);
  auto res = runLLcode(P, D);
  for (const auto &it : res.first)
    printf("%I64d\n", it);
  return 0;
}
