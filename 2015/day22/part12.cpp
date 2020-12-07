#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define mp make_pair
#define CHECK(x) if(!(x)) return false;
#define CHECKRET(x, y) if(!(x)) return (y);
#define SKIP(x) if((x)) continue;
typedef pair<int, int> pii;

#define RELAX(x, y) { auto tmp = (x); best = min(best, mp(tmp.first, string(y) + tmp.second)); }

bool hardmode = false;

pair<int, string> playerTurn(int hp, int mana, int bosshp, int bossdmg, int poisonleft, int armorleft, int rechargeleft, int manaspent);

pair<int, string> bossTurn(int hp, int mana, int bosshp, int bossdmg, int poisonleft, int armorleft, int rechargeleft, int manaspent) {
  pair<int, string> best = mp(INT_MAX, "");
  CHECKRET(mana >= 0, best);
  CHECKRET(hp > 0, best);
  int armor = 0;
  if (poisonleft >= 1) poisonleft -= 1, bosshp -= 3;
  if (armorleft >= 1) armorleft -= 1, armor = 7;
  if (rechargeleft >= 1) rechargeleft -= 1, mana += 101;
  if (bosshp <= 0) return mp(manaspent, "");
  hp -= max(0, bossdmg - armor);
  return playerTurn(hp, mana, bosshp, bossdmg, poisonleft, armorleft, rechargeleft, manaspent);
}

pair<int, string> playerTurn(int hp, int mana, int bosshp, int bossdmg, int poisonleft, int armorleft, int rechargeleft, int manaspent) {
  pair<int, string> best = mp(INT_MAX, "");
  if (hardmode) --hp;
  CHECKRET(mana >= 0, best);
  CHECKRET(hp > 0, best);
  int armor = 0;
  if (poisonleft >= 1) poisonleft -= 1, bosshp -= 3;
  if (armorleft >= 1) armorleft -= 1, armor = 7;
  if (rechargeleft >= 1) rechargeleft -= 1, mana += 101;
  if (bosshp <= 0) return mp(manaspent, "");
  CHECKRET(manaspent <= 2000, best);
  RELAX(bossTurn(hp, mana - 53, bosshp - 4, bossdmg, poisonleft, armorleft, rechargeleft, manaspent + 53), "M ");
  RELAX(bossTurn(hp + 2, mana - 73, bosshp - 2, bossdmg, poisonleft, armorleft, rechargeleft, manaspent + 73), "D ");
  if (armorleft == 0) RELAX(bossTurn(hp, mana - 113, bosshp, bossdmg, poisonleft, 6, rechargeleft, manaspent + 113), "S ");
  if (poisonleft == 0) RELAX(bossTurn(hp, mana - 173, bosshp, bossdmg, 6, armorleft, rechargeleft, manaspent + 173), "P ");
  if (rechargeleft == 0) RELAX(bossTurn(hp, mana - 229, bosshp, bossdmg, poisonleft, armorleft, 5, manaspent + 229), "R ");
  return best;
}

int main() {
  auto res = playerTurn(50, 500, 51, 9, 0, 0, 0, 0);
  printf("Part 1 %d %s\n", res.first, res.second.c_str());
  hardmode = true;
  res = playerTurn(50, 500, 51, 9, 0, 0, 0, 0);
  printf("Part 2 %d %s\n", res.first, res.second.c_str());
  return 0;
}
