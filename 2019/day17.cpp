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
  else assert(0);
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

char buffer[1000];

int main() {
  //freopen("fis.in", "r", stdin);
  //freopen("fis.out", "w", stdout);
  ifstream fin("fis.in");
  //ifstream fout("fis.out");
  string s;
  fin >> s;
  replace(s.begin(), s.end(), ',', ' ');
  vector<LL> P;
  LL x, aux;
  for (LL offset = 0; sscanf(s.c_str() + offset, "%I64d%lln", &x, &aux) >= 0; offset += aux, P.push_back(x));
  P.resize(1000000000);
  deque<LL> D;
  P[0] = 2;
  //D.push_back('A');
  //D.push_back('\n');
  LL eip = 0;
  while (1) {
    auto res = runLLcode(P, D, eip);
    eip = res.second.first;
    for (const auto &it : res.first) {
      if (it >= 255) printf("%I64d\n", it);
      else putchar((char)it);
    }

    scanf("%s", buffer);
    for (char *i = buffer; *i; ++i) D.push_back(*i);
    D.push_back('\n');
  }
  return 0;
}

char mat[100][100];
bool viz[100][100];
int N, M;

bool intersection(int x, int y) {
  return mat[x][y] == '#' &&
    mat[x - 1][y] == '#' && mat[x][y - 1] == '#' && mat[x + 1][y] == '#' && mat[x][y + 1] == '#';

}

vector<string> getAllLines() {
  vector<string> v;
  string s;
  while (getline(cin, s)) {
    SKIP(s.size() <= 0);
    v.push_back(s);
  }
  return v;
}

void setCursorPosition(int x, int y) {
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  fflush(stdout);
  COORD coord = { (SHORT)x, (SHORT)y };
  SetConsoleCursorPosition(hOut, coord);
}

int pi, pj;
char curMove = '^';
void printMat() {
  setCursorPosition(0, 0);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      if (i == pi && j == pj) {
        putchar(curMove);
        continue;
      }
      if (mat[i][j] != '#') {
        putchar(mat[i][j]);
        continue;
      }
      if (viz[i][j]) putchar('o');
      else putchar('X');
    }
    putchar('\n');
  }
}

bool beenLooping(string &movement) {
  CHECK(movement.size() >= 4);
  for (int i = (int)movement.size() - 4; i < movement.size(); ++i)
    CHECK(movement[i] != 'F');
  return true;
}

void sleepFor(double secs) {
  clock_t t0 = clock();
  while (1.0 * (clock() - t0) / CLOCKS_PER_SEC < secs);
}

bool validSq(int nxti, int nxtj) {
  return !((nxti < 0 || nxtj < 0 || nxti >= N || nxtj >= M) || (mat[nxti][nxtj] == '.'));
}

int main2() {
  freopen("fis.out", "r", stdin);
  vector<string> lines = getAllLines();
  N = (int)lines.size();
  M = (int)lines[0].size();
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j) {
      mat[i][j] = lines[i][j];
      if (mat[i][j] == '^') pi = i, pj = j;
    }
  string movement;
  while (1) {
    //printMat(); sleepFor(0.05);
    if (!validSq(pi, pj)) break;
    viz[pi][pj] = true;
    int nxti = pi, nxtj = pj;
    char mchar = 'F';
    if (curMove == '^') nxti = pi - 1, nxtj = pj;
    if (curMove == '<') nxti = pi, nxtj = pj - 1;
    if (curMove == 'v') nxti = pi + 1, nxtj = pj;
    if (curMove == '>') nxti = pi, nxtj = pj + 1;
    if (!beenLooping(movement)) {
      if (!validSq(nxti, nxtj) || viz[nxti][nxtj]) {
        if (curMove == '^') mchar = '>';
        if (curMove == '<') mchar = '^';
        if (curMove == 'v') mchar = '<';
        if (curMove == '>') mchar = 'v';
      }
    }
    else {
      for (int i = 0; i < 4; ++i) movement.pop_back();
    }
    if (mchar == 'F') pi = nxti, pj = nxtj;
    else curMove = mchar;
    movement.push_back(mchar == 'F' ? 'F' : 'R');
  }
  printMat();
  puts(movement.c_str());
  return 0;
}

#include <regex>
bool ok(string m, string A, string B, string C) {
  m = regex_replace(m, regex(A), "A");
  m = regex_replace(m, regex(B), "B");
  m = regex_replace(m, regex(C), "C");
  for (const auto &it : m) {
    CHECK(it == 'A' || it == 'B' || it == 'C');
  }
  return true;
}

bool proc(string &m) {
  int n = (int)m.size();
  int sa = 0;
  for (int la = 5; la <= 12; ++la)
    for (int sb = sa + la - 1; sb < n; ++sb)
      for (int lb = 5; lb <= 12; ++lb)
        for (int sc = sb + lb - 1; sc < n; ++sc)
          for (int lc = 5; lc <= 12; ++lc) {
            cout << sa << " " << sb << " " << sc << " " << endl;
            string A = m.substr(sa, la), B = m.substr(sb, lb),
              C = m.substr(sc, lc);
            SKIP(!ok(m, A, B, C));
            cout << m << endl << A << endl << B << endl << C << endl;
            return true;
          }
  return false;
}

int main3() {
  string s = "L6R12L4L6R6L6R12R6L6R12L6L10L10R6L6R12L4L6R6L6R12L6L10L10R6L6R12L4L6R6L6R12L6L10L10R7";
  cout << proc(s) << endl;
  return 0;
}
