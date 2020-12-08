#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define mp make_pair
#define CHECK(x) if(!(x)) return false;
#define CHECKRET(x, y) if(!(x)) return (y);
#define SKIP(x) if((x)) continue;
typedef pair<int, int> pii;

int x, y, z;

bool can() {
  CHECK(x + y > z);
  CHECK(y + z > x);
  CHECK(z + x > y);
  return true;
}

int main() {
  freopen("in", "r", stdin);
  int s = 0;
  while (scanf("%d%d%d", &x, &y, &z) != EOF) {
    s += can();
  }
  printf("%d\n", s);
  return 0;
}
