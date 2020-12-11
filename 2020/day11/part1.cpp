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

struct state {
  vector< vector<int> > floors;
  int elevator;

  bool noboom(int floormsk = -1) {
    vector<int> r, m;
    for (int fi = 0; fi < (int)floors.size(); ++fi) {
      SKIP(!(floormsk & (1 << fi)));
      r.clear(), m.clear();
      for (auto& i : floors[fi]) {
        if (i < 0) m.push_back(i);
        else r.push_back(i);
      }
      sort(r.begin(), r.end());
      for (auto& mcr : m) {
        SKIP(binary_search(r.begin(), r.end(), -mcr));
        CHECK(r.empty());
      }
    }
    return true;
  }
};

LL encode(state& st) {
  LL s = 0;
  for (auto& fl : st.floors) {
    s <<= 15;
    for (auto& e : fl) {
      if (e < 0) s |= (1LL << ((-e) + 7));
      else s |= (1LL << e);
    }
  }
  s <<= 2;
  assert(st.elevator >= 0 && st.elevator < 4);
  s += st.elevator;
  return s;
}

void decode(LL ccode, state& st) {
  LL code = ccode;
  st.floors.clear();
  st.floors.resize(4);
  st.elevator = (code & ((1 << 2) - 1));
  code >>= 2;
  for (int i = 3; i >= 0; --i, code >>= 15) {
    for (int b = 0; b < 15; ++b) {
      SKIP((code & (1LL << b)) == 0);
      int x = b;
      if (x > 7) x = -(x - 7);
      st.floors[i].push_back(x);
    }
  }
  //assert(ccode == encode(st));
}

LL getFinalState(int part) {
  state s;
  s.floors.resize(4);
  for (int i = 1; i <= ((part == 1) ? 5 : 7); ++i)
    s.floors.back().push_back(i), s.floors.back().push_back(-i);
  s.elevator = 3;
  return encode(s);
}

void transferToFloor(state& f, int fl, int fi, int tf) {
  f.floors[tf].push_back(f.floors[fl][fi]);
  swap(f.floors[fl][fi], f.floors[fl][f.floors[fl].size() - 1]);
  f.floors[fl].pop_back();
}

void putNeighbors(state& st, vector<LL>& wh) {
  wh.clear();
  state newstate;
  int n = (int)st.floors[st.elevator].size();
  for (newstate.elevator = st.elevator - 1; newstate.elevator <= st.elevator + 1; newstate.elevator += 2) {
    SKIP(!(newstate.elevator >= 0 && newstate.elevator < 4));
    for (int i = -1; i < n; ++i)
      for (int j = i + 1; j <= n; ++j) {
        SKIP(i < 0 && j >= n);
        newstate.floors = st.floors;
        if (j < n)  transferToFloor(newstate, st.elevator, j, newstate.elevator);
        if (i >= 0) transferToFloor(newstate, st.elevator, i, newstate.elevator);
        if (newstate.noboom()) wh.push_back(encode(newstate));
      }
  }
}

map<LL, int> dst;

int BFS(LL s, LL tar) {
  queue<LL> Q;
  Q.push(s);
  dst[s] = 0;
  state ts;
  vector<LL> ngh;
  while (!Q.empty()) {
    LL t = Q.front();
    Q.pop();
    decode(t, ts);
    putNeighbors(ts, ngh);
    //printf("%d %d\n", dst[t], (int)dst.size());
    //printf("I have %d nghs\n", (int)ngh.size());
    for (auto& it : ngh) {
      SKIP(dst.count(it));
      dst[it] = dst[t] + 1;
      Q.push(it);
      if (it == tar) return dst[it];
    }
  }
  return dst[tar];
}

char mat[2][200][200];
int N = 0, M = 0;
int cur = 0, old = 1;

int getOccupiedNgh(int i, int j) {
  int cnt = 0;
  for(int ii = i-1; ii <=i + 1; ++ii)
    for (int jj = j - 1; jj <= j + 1; ++jj) {
      SKIP(jj < 0 || ii < 0);
      SKIP(jj >= M || ii >= N);
      SKIP(ii == i && jj == j);
      cnt += (mat[old][ii][jj] == '#');
    }
  return cnt;
}

void printMat() {
  for (int i = 0; i < N; ++i)
    puts(mat[cur][i]);
  puts("");
}

int main() {
  freopen("in", "r", stdin);
  while (scanf("%s", mat[0][N++]) != EOF);
  M = strlen(mat[0][0]);
  bool flag = true;
  while (flag) {
    flag = false;
    swap(cur, old);
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < M; ++j) {
        mat[cur][i][j] = mat[old][i][j];
        int ngh = getOccupiedNgh(i, j);
        if (mat[cur][i][j] == 'L' && ngh == 0) {
          mat[cur][i][j] = '#';
          flag = true;
        }
        if (mat[cur][i][j] == '#' && ngh >= 4) {
          mat[cur][i][j] = 'L';
          flag = true;
        }
      }
    //printMat();
    //break;
  }
  int cnt = 0;
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
      if (mat[cur][i][j] == '#')
        ++cnt;
  printf("%d\n", cnt);
  return 0;
}
