#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
typedef long long LL;
#define mp make_pair
#define CHECK(x) if(!(x)) return false;
#define CHECKRET(x, y) if(!(x)) return (y);
#define SKIP(x) if((x)) continue;
typedef pair<int, int> pii;
typedef deque<int> dq;

vector<string> getAllLines() {
  vector<string> v;
  string s;
  while (getline(cin, s)) {
    SKIP(s.size() <= 0);
    v.push_back(s);
  }
  return v;
}

dq tokenize(string s, char by) {
  replace(s.begin(), s.end(), by, ' ');
  int x, aux;
  dq P;
  for (int offset = 0; sscanf(s.c_str() + offset, "%d%n", &x, &aux) >= 0; offset += aux, P.push_back(x));
  return P;
}

int toInt(string s) {
  int x;
  sscanf(s.c_str(), "%d", &x);
  return x;
}

struct node {
  int x;
  node* prv, * nxt;
};

node* head = NULL, *tail = NULL;
node* locs[1000010];

void pushBack(int x) {
  node *n = (node*)(malloc(sizeof node));
  if (n == NULL) return;
  n->x = x;
  if (head == NULL) {
    n->prv = n->nxt = NULL;
    head = tail = n;
  }
  else {
    n->nxt = NULL;
    n->prv = tail;
    tail->nxt = n;
    tail = n;
  }
}

node *nextNode(node* x) {
  if (x->nxt == NULL) return head;
  return x->nxt;
}

int main() {
  freopen("in", "r", stdin);
  string inp = "789465123";
  int mx = 0;
  for (int i = 0; i < 9; ++i) {
    int x = (i < (int)inp.size()) ? (inp[i] - '0') : (i + 1);
    mx = max(mx, x);
    pushBack(x);
    locs[x] = tail;
  }
  tail->nxt = head;
  head->prv = tail;

  int steps = 100;
  node *cur = head;
  vector<node*> r;
  while (steps--) {
    r.clear();
    node* curBack = cur;
    int lbl = cur->x;
    cur = nextNode(cur);
    for (int x = 0; x < 3; ++x, cur = nextNode(cur)) {
      r.push_back(cur);
    }
    curBack->nxt = cur;
    cur->prv = curBack;
    while (1) {
      --lbl;
      if (lbl <= 0) lbl = mx;
      node* idx = locs[lbl];
      SKIP(count(r.begin(), r.end(), idx));
      node* nxtIdx = idx->nxt;
      idx->nxt = r[0]; r[0]->prv = idx;
      r[2]->nxt = nxtIdx; nxtIdx->prv = r[2];
      break;
    }
  }
  cur = locs[1]; cur = cur->nxt;
  for (int i = 0; i < 8; ++i, cur = cur->nxt)
    printf("%d", cur->x);
  return 0;
}
