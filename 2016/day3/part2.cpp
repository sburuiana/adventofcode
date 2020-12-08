#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define mp make_pair
#define CHECK(x) if(!(x)) return false;
#define CHECKRET(x, y) if(!(x)) return (y);
#define SKIP(x) if((x)) continue;
typedef pair<int, int> pii;

bool can(int x, int y, int z) {
  CHECK(x + y > z);
  CHECK(y + z > x);
  CHECK(z + x > y);
  return true;
}

int main() {
  freopen("in", "r", stdin);
  int s = 0;
  int x1, y1, z1, x2 , y2, z2, x3, y3, z3;
  while (scanf("%d%d%d%d%d%d%d%d%d", &x1, &x2, &x3, &y1, &y2, &y3, &z1, &z2, &z3) != EOF) {
    s += can(x1, y1, z1);
    s += can(x2, y2, z2);
    s += can(x3, y3, z3);
  }
  printf("%d\n", s);
  return 0;
}
