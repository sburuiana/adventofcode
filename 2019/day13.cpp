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

const int SZ1 = 30;
const int SZ2 = 50;
char mat[SZ1][SZ2 + 1];

void setCursorPosition(int x, int y) {
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  fflush(stdout);
  COORD coord = { (SHORT)x, (SHORT)y };
  SetConsoleCursorPosition(hOut, coord);
}


void printMat() {
  setCursorPosition(0, 0);
  for (int i = 0; i < SZ1; ++i)
    puts(mat[i]);
  puts("");
}

/*
0 is an empty tile. No game object appears in this tile.
1 is a wall tile. Walls are indestructible barriers.
2 is a block tile. Blocks can be broken by the ball.
3 is a horizontal paddle tile. The paddle is indestructible.
4 is a ball tile. The ball moves diagonally and bounces off objects.
*/

char typeToChar(int tip) {
  if (tip == 0) return ' ';
  if (tip == 1) return '#';
  if (tip == 2) return '%';
  if (tip == 3) return '_';
  if (tip == 4) return 'o';
  return ' ';
}

int main() {
  //freopen("fis.in", "r", stdin);
  string s;
  ifstream fin("fis.in");
  fin >> s;
  replace(s.begin(), s.end(), ',', ' ');
  vector<LL> P;
  LL x, aux;
  for (LL offset = 0; sscanf(s.c_str() + offset, "%I64d%lln", &x, &aux) >= 0; offset += aux, P.push_back(x));
  P.resize(100000000);
  P[0] = 2;
  deque<LL> D;
  D.push_back(2);
  for (int i = 0; i < SZ1; ++i)
    for (int j = 0; j < SZ2; ++j)
      mat[i][j] = ' ';
  LL eip = 0;
  LL steps = 0;
  while (1) {
    LL cnt = 0, scor = 0;
    auto res = runLLcode(P, D, eip);
    pii paddleCoords = mp(0LL, 0LL);
    pii ballCoords = mp(0LL, 0LL);
    for (LL i = 0; i < (LL)res.first.size(); i += 3) {
      LL x = res.first[i], y = res.first[i + 1], tip = res.first[i + 2];
      if (tip == 2) ++cnt;
      if (tip == 3) paddleCoords = mp(x, y);
      if (tip == 4) ballCoords = mp(x, y);
      assert(x < SZ2 && y < SZ1);
      if (x == -1 && y == 0) scor = tip;
      mat[y][x] = typeToChar((int)tip);
    }
    //printMat();
    if (cnt == 0) {
      //printf("%I64d\n", scor);
      //break;
    }
    if (ballCoords.second >= paddleCoords.second) {
      puts("U LOST :(");
      break;
    }
    LL inp = 0;
    if (paddleCoords.first < ballCoords.first) inp = 1;
    else if (paddleCoords.first > ballCoords.first) inp = -1;
    /*
    string buf;
    if(steps >= 5000) getline(cin, buf);
    if (buf.size() == 0)
      inp = 0;
    else sscanf(buf.c_str(), "%I64d", &inp);
    */
    D.push_back(inp);
    printf("STEP : %I64d, cnt = %I64d, scor = %I64d\n", ++steps, cnt, scor);
  }
  
  //puts(mat[0]);
  return 0;
}
