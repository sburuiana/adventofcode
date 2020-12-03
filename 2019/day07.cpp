#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define mp make_pair
#define CHECK(x) if(!(x)) return false;
#define CHECKRET(x, y) if(!(x)) return (y);
#define SKIP(x) if((x)) continue;
typedef pair<int, int> pii;

int getParam(int opIdx, int argIdx, vector<int> &P) {
  int mode = P[opIdx] / 100;
  for (int i = 0; i < argIdx - 1; mode /= 10, ++i);
  mode %= 10;
  argIdx += opIdx;
  if (mode == 0) return P[P[argIdx]];
  else return P[argIdx];
}

#define TERNARY_OPERATOR(op) P[P[eip + 3]] = (int)(getParam(eip, 1, P) op getParam(eip, 2, P)); eip += 4;

pair<vector<int>, pii> runIntcode(vector<int> &P, deque<int> &inputs, int eip = 0) {
  vector<int> outputs;
  while (eip < (int)P.size()) {
    switch (P[eip] % 100) {
    case 99:
      eip = INT_MAX; break;
    case 1:
      TERNARY_OPERATOR(+); break;
    case 2:
      TERNARY_OPERATOR(*); break;
    case 3: {
      if (inputs.empty()) return mp(outputs, mp(eip, 0));
      P[P[eip + 1]] = inputs.front();
      inputs.pop_front();
      eip += 2;
      break;
    }
    case 4:
      //printf("%d\n", getParam(eip, 1, P));
      outputs.push_back(getParam(eip, 1, P));
      eip += 2;
      break;
    case 5:
      eip = getParam(eip, 1, P) ? getParam(eip, 2, P) : (eip + 3);
      break;
    case 6:
      eip = getParam(eip, 1, P) ? (eip + 3) : getParam(eip, 2, P);
      break;
    case 7:
      TERNARY_OPERATOR(< );
      break;
    case 8:
      TERNARY_OPERATOR(== );
      break;
    default:
      break;
    }
  }
  return mp(outputs, mp(eip, 1));
}

int tryCombination(vector<int> &P, vector<int> &perm) {
  vector< pair< vector<int>, pair< deque<int>, int > > > progs;
  for (int i = 0; i < 5; ++i) {
    progs.push_back(mp(P, mp(deque<int>(), 0)));
    progs.back().second.first.push_back(perm[i]);
  }
  progs[0].second.first.push_back(0);
  int lastEInp = 0;
  bool flag = true;
  while (flag) {
    flag = false;
    for (int i = 0; i < 5; ++i) {
      //printf("Running program #%d\n", i);
      auto res = runIntcode(progs[i].first, progs[i].second.first, progs[i].second.second);
      progs[i].second.second = res.second.first;
      for (const auto &it : res.first) {
        progs[(i + 1) % 5].second.first.push_back(it);
        if (i == 4) lastEInp = it;
      }
      if (!res.second.second) flag = true;
    }
  }
  return lastEInp;
}

int main() {
  freopen("fis.in", "r", stdin);
  string s;
  cin >> s;
  replace(s.begin(), s.end(), ',', ' ');
  vector<int> P;
  int x, aux;
  for (int offset = 0; sscanf(s.c_str() + offset, "%d%n", &x, &aux) >= 0; offset += aux, P.push_back(x));
  //printf("%d\n", runIntcode(P, { }, { }));
  int mx = 0;
  vector<int> perm({ 5, 6, 7, 8, 9 });
  //reverse(perm.begin(), perm.end());
  do {
    mx = max(mx, tryCombination(P, perm));
    //break;
  } while (next_permutation(perm.begin(), perm.end()));
  printf("%d\n", mx);
  return 0;
}
