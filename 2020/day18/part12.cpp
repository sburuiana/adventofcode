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

class _prec {
private:
	vector<char> v;
public:
	_prec(int part) {
		v.resize(255);
		memset(&v[0], 0, sizeof(v[0]) * v.size());
		v['('] = 1;
		v['+'] = v['-'] = part + 1;
		v['*'] = v['/'] = 2;
	}
	char operator()(char c) {
		return v[c];
	}
} prec1(1), prec2(2);

LL mat_eval(char op, LL n1, LL n2) {
	switch (op)
	{
	case '+':
		return n2 + n1;
	case '-':
		return n2 - n1;
	case '*':
		return n2 * n1;
	case '/':
		return n2 / n1;
	default:
		break;
	}
	return 0;
}

void mktree(stack<char>& S1, stack<LL>& S2) {
	char op = S1.top();
	S1.pop();
	LL n1 = S2.top();
	S2.pop();
	LL n2 = S2.top();
	S2.pop();
	S2.push(mat_eval(op, n1, n2));
}

LL parseinput(string sinput, _prec &prec) {
	stack<char> S1; stack<LL> S2;
	LL curNr = 0; bool inNr = false;
	for(char &c : sinput) {
	//while ((c = getchar()) && !feof(stdin)) {
		if (c <= '9' && c >= '0') {
			curNr = curNr * 10 + c - '0';
			inNr = true;
			continue;
		}
		if (inNr) {
			S2.push(curNr);
			curNr = 0;
			inNr = false;
		}
		if (c == '(')
			S1.push(c);
		else if (prec(c)) {
			while (!S1.empty() && prec(c) <= prec(S1.top()))
				mktree(S1, S2);
			S1.push(c);
		}
		else if (c == ')') {
			while (S1.top() != '(')
				mktree(S1, S2);
			S1.pop();
		}
	}
	if (inNr) {
		S2.push(curNr);
		curNr = 0;
		inNr = false;
	}
	while (!S1.empty())
		mktree(S1, S2);
	return S2.top();
	//printf("%d\n", S2.top());
	//S2.pop();
}

int main() {
  freopen("in", "r", stdin);
	LL ans_part1 = 0, ans_part2 = 0;
	for (string& line : getAllLines()) {
		ans_part1 += parseinput(line, prec1);
		ans_part2 += parseinput(line, prec2);
	}
	printf("Part 1 : %I64d\nPart 2 : %I64d\n", ans_part1, ans_part2);
  return 0;
}
