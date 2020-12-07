#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define mp make_pair
#define CHECK(x) if(!(x)) return false;
#define CHECKRET(x, y) if(!(x)) return (y);
#define SKIP(x) if((x)) continue;
typedef pair<int, int> pii;

struct item {
  int cost, dmg, armor;
  item(int cost, int dmg, int armor) : cost(cost), dmg(dmg), armor(armor) {}
  void adu(item& x) {
    cost += x.cost;
    dmg += x.dmg;
    armor += x.armor;
  }
};

vector<item> weapons, armor, rings;

bool canWin(int hp, int dmg, int armor, int bosshp, int bossdmg, int bossarmor) {
  dmg -= bossarmor;
  if (dmg < 1) dmg = 1;
  bossdmg -= armor;
  if (bossdmg < 1) bossdmg = 1;
  int playerTurns = bosshp / dmg;
  if (bosshp % dmg != 0) ++playerTurns;
  int bossTurns = hp / bossdmg;
  if (hp % bossdmg != 0) ++bossTurns;
  return playerTurns <= bossTurns;
}

int main() {
  weapons.push_back(item(8, 4, 0));
  weapons.push_back(item(10, 5, 0));
  weapons.push_back(item(25, 6, 0));
  weapons.push_back(item(40, 7, 0));
  weapons.push_back(item(74, 8, 0));
  armor.push_back(item(13, 0, 1));
  armor.push_back(item(31, 0, 2));
  armor.push_back(item(53, 0, 3));
  armor.push_back(item(75, 0, 4));
  armor.push_back(item(102, 0, 5));
  rings.push_back(item(25, 1, 0));
  rings.push_back(item(50, 2, 0));
  rings.push_back(item(100, 3, 0));
  rings.push_back(item(20, 0, 1));
  rings.push_back(item(40, 0, 2));
  rings.push_back(item(80, 0, 3));
  int best1 = INT_MAX, best2 = 0;
  for (auto& w : weapons)
    for (int ai = -1; ai < (int)armor.size(); ++ai)
      for (int ri1 = -2; ri1 < (int)rings.size(); ++ri1)
        for (int ri2 = ri1 + 1; ri2 < (int)rings.size(); ++ri2) {
          item stats(0, 0, 0);
          stats.adu(w);
          if (ai >= 0) stats.adu(armor[ai]);
          if (ri1 >= 0) stats.adu(rings[ri1]);
          if (ri2 >= 0) stats.adu(rings[ri2]);
          if (canWin(100, stats.dmg, stats.armor, 109, 8, 2))
            best1 = min(best1, stats.cost);
          else best2 = max(best2, stats.cost);
        }
  printf("Part1 %d\n", best1);
  printf("Part2 %d\n", best2);
  return 0;
}
