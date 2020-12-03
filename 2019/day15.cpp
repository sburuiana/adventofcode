#include <Windows.h>
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
  else if (mode == 1) return P[argIdx];
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
      //puts("FEED ME INPUT!");
      if (inputs.empty()) return mp(outputs, mp(eip, 0));
      getParam(eip, 1, P, rb) = inputs.front();
      inputs.pop_front();
      eip += 2;
      break;
    }
    case 4:
      //printf("%I64d\n", getParam(eip, 1, P, rb));
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
  return mp(outputs, mp(eip, 1));
}

char typeToChar(int tip) {
  if (tip == 0) return ' ';
  if (tip == 1) return '#';
  if (tip == 2) return '%';
  if (tip == 3) return '_';
  if (tip == 4) return 'o';
  return ' ';
}

map< pii, int > dst;
map< pii, char > mat;
pii tar;

int d[] = { -1, 0, 1, 0, 0, -1, 0, 1 };
int dop[] = { 1, 0, 3, 2 };

vector<LL> P;
LL eip = 0;
deque<LL> D;

void explore(pii x) {
  printf("Exploring %I64d %I64d\n", x.first, x.second);
  mat[x] = '.';
  for (int di = 0; di < 4; ++di) {
    pii nx = mp(x.first + d[di * 2], x.second + d[di * 2 + 1]);
    if (mat.count(nx)) continue;
    D.push_back(di + 1);
    auto res = runLLcode(P, D, eip);
    eip = res.second.first;
    LL outp = res.first[0];
    printf("%d --> %I64d\n", di + 1, outp);
    if (outp != 0) {
      if (outp == 2) tar = nx;
      explore(nx);
      printf("Revering %d with %d\n", di + 1, dop[di] + 1);
      D.push_back(dop[di] + 1);
      res = runLLcode(P, D, eip);
      eip = res.second.first;
      assert(res.first[0] != 0);
    }
  }
}

LL BFS(pii st, int part) {
  dst.clear();
  dst[st] = 0;
  queue<pii> Q;
  Q.push(st);
  while (!Q.empty()) {
    pii x = Q.front();
    Q.pop();
    for (int di = 0; di < 4; ++di) {
      pii nx = mp(x.first + d[di * 2], x.second + d[di * 2 + 1]);
      SKIP(!mat.count(nx));
      SKIP(dst.count(nx));
      dst[nx] = dst[x] + 1;
      Q.push(nx);
    }
  }
  if(part == 1) return dst[tar];
  else if (part == 2) {
    LL mx = 0;
    for (const auto &it : dst)
      mx = max(mx, it.second);
    return mx;
  }
  assert(0);
  return 0;
}

int main() {
  //freopen("fis.in", "r", stdin);
  string s;
  ifstream fin("fis.in");
  fin >> s;
  replace(s.begin(), s.end(), ',', ' ');
  LL x, aux;
  for (LL offset = 0; sscanf(s.c_str() + offset, "%I64d%lln", &x, &aux) >= 0; offset += aux, P.push_back(x));
  P.resize(100000000);
  tar = mp(INT_MIN, INT_MIN);
  explore(mp(0, 0));
  puts("Done exploring");
  printf("%I64d\n", BFS(mp(0, 0), 1));
  printf("%I64d\n", BFS(tar, 2));

  return 0;
}
