#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define mp make_pair
#define CHECK(x) if(!(x)) return false;
#define CHECKRET(x, y) if(!(x)) return (y);
#define SKIP(x) if((x)) continue;
typedef pair<int, int> pii;

string input = "109,424,203,1,21101,0,11,0,1105,1,282,21101,18,0,0,1105,1,259,2101,0,1,221,203,1,21102,1,31,0,1105,1,282,21101,0,38,0,1106,0,259,21002,23,1,2,22101,0,1,3,21101,0,1,1,21102,1,57,0,1106,0,303,2102,1,1,222,21001,221,0,3,20102,1,221,2,21101,0,259,1,21101,80,0,0,1106,0,225,21101,0,23,2,21102,91,1,0,1106,0,303,1201,1,0,223,20101,0,222,4,21101,0,259,3,21102,1,225,2,21102,1,225,1,21102,1,118,0,1105,1,225,20102,1,222,3,21101,0,87,2,21101,133,0,0,1106,0,303,21202,1,-1,1,22001,223,1,1,21101,0,148,0,1105,1,259,2101,0,1,223,20102,1,221,4,21002,222,1,3,21101,0,9,2,1001,132,-2,224,1002,224,2,224,1001,224,3,224,1002,132,-1,132,1,224,132,224,21001,224,1,1,21102,1,195,0,106,0,109,20207,1,223,2,21001,23,0,1,21102,1,-1,3,21101,0,214,0,1106,0,303,22101,1,1,1,204,1,99,0,0,0,0,109,5,2102,1,-4,249,21201,-3,0,1,22101,0,-2,2,21202,-1,1,3,21102,250,1,0,1106,0,225,21202,1,1,-4,109,-5,2106,0,0,109,3,22107,0,-2,-1,21202,-1,2,-1,21201,-1,-1,-1,22202,-1,-2,-2,109,-3,2105,1,0,109,3,21207,-2,0,-1,1206,-1,294,104,0,99,21202,-2,1,-2,109,-3,2105,1,0,109,5,22207,-3,-4,-1,1206,-1,346,22201,-4,-3,-4,21202,-3,-1,-1,22201,-4,-1,2,21202,2,-1,-1,22201,-4,-1,1,22102,1,-2,3,21102,1,343,0,1106,0,303,1106,0,415,22207,-2,-3,-1,1206,-1,387,22201,-3,-2,-3,21202,-2,-1,-1,22201,-3,-1,3,21202,3,-1,-1,22201,-3,-1,2,21201,-4,0,1,21102,384,1,0,1105,1,303,1106,0,415,21202,-4,-1,-4,22201,-4,-3,-4,22202,-3,-2,-2,22202,-2,-4,-4,22202,-3,-2,-3,21202,-4,-1,-2,22201,-3,-2,1,21202,1,1,-4,109,-5,2106,0,0";

int &getParam(int opIdx, int argIdx, map<int, int> &P, int relBase) {
  int mode = P[opIdx] / 100;
  for (int i = 0; i < argIdx - 1; mode /= 10, ++i);
  mode %= 10;
  argIdx += opIdx;
  if (mode == 0) return P[P[argIdx]];
  else if (mode == 1) return P[argIdx];
  else if (mode == 2) return P[P[argIdx] + relBase];
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


#define TERNARY_OPERATOR(op) getParam(eip, 3, P, rb) = (int)(getParam(eip, 1, P, rb) op getParam(eip, 2, P, rb)); eip += 4;

pair<vector<int>, pair<int, int> > runLLcode(map<int, int> P, queue<int> &inputs, int eip = 0) {
  int rb = 0;
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

const int N = 2000, M = 2000;
const int SX = 100, SY = 100;
char mat[N + 10][M + 10];

bool fitsSquare(int x, int y) {
  int lx = x + SX - 1, ly = y + SY - 1;
  for (int i = x; i <= lx; ++i) {
    CHECK(mat[i][y] == '#');
    CHECK(mat[i][ly] == '#');
  }
  for (int j = y; j <= ly; ++j) {
    CHECK(mat[x][j] == '#');
    CHECK(mat[lx][j] == '#');
  }
  return true;
}

int eudist(pii x) {
  return x.first * x.first + x.second * x.second;
}

int main_helper() {
  freopen("fis.in", "r", stdin);
  freopen("fis.out", "w", stdout);

  string s;
  cin >> s;
  replace(s.begin(), s.end(), ',', ' ');
  vector<int> PP;
  int x, aux;
  for (int offset = 0; sscanf(s.c_str() + offset, "%I32d%n", &x, &aux) >= 0; offset += aux, PP.push_back(x));
  map<int, int> P;
  for (int i = 0; i < (int)PP.size(); ++i) P[i] = PP[i];
  //P.resize(1000000000);
  int ans = 0;
  //D.push_back(2);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      queue<int> D;
      D.push(i);
      D.push(j);
      auto res = runLLcode(P, D);
      for (const auto &it : res.first) {
        if (it == 1) {
          mat[i][j] = '#';
          ++ans;
        }
        else mat[i][j] = '.';
        //cout << it << endl;
      }
    }
    //cout << i << endl;
    //fflush(stdout);
  }
  //printf("%d\n", ans);

  for (int i = 0; i < N; ++i)
    puts(mat[i]);
  fflush(stdout);
  return 0;
}

int main() {
  //return main_helper();
  freopen("fis.out", "r", stdin);
  vector<string> lines = getAllLines();
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
      mat[i][j] = lines[i][j];

  pii bestPt = mp(-1, -1);
  for (int i = 0; i < N - SX; ++i)
    for (int j = 0; j < M - SY; ++j) {
      SKIP(!fitsSquare(i, j));
      if (bestPt.first < 0 || eudist(mp(i, j)) < eudist(bestPt))
        bestPt = mp(i, j);
    }
  printf("%d\n", bestPt.first * 10000 + bestPt.second);
  return 0;
}
