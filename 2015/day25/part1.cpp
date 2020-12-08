#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define mp make_pair
#define CHECK(x) if(!(x)) return false;
#define CHECKRET(x, y) if(!(x)) return (y);
#define SKIP(x) if((x)) continue;
typedef pair<int, int> pii;

int mat[10000][10000];
int tari = 2947, tarj = 3029;

int getNext(int x) {
  return (int)(1LL * x * 252533 % 33554393);
}

int main() {
  int cur = 20151125;
  for (int cnt = 1; ; ++cnt)
    for (int i = cnt, j = 1; i >= 1; --i, ++j) {
      mat[i][j] = cur;
      if (i == tari && j == tarj) {
        printf("%d\n", mat[i][j]);
        return 0;
      }
      cur = getNext(cur);
    }
  return 0;
}
