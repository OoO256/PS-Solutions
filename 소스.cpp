#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>
#define MAXN 1000000
using namespace std;
typedef pair<int, int> ii;
int result[MAXN + 1];
int where[MAXN + 1];
int testcase, n, ntest=0, endp;
bool ans;
char c;
map<char, int>ma;
inline void test() {
	if (endp == 0)
		return;
	for (; endp > 0; endp--) {
		if (where[endp] != result[endp])
			break;
	}
	if (endp == 0)
		ans = true;
}
inline void pmove(int curr, int from, int to);

inline void move(int curr, int from, int to) {

	if (ans)
		return;

	int rest = 3 - from - to;
	if ((from == 0 && to == 1) || (from == 1 && to == 2) || (from == 2 && to == 0)) {
		///*
		if (from != result[curr] || endp - curr>0) {
			where[curr] = to;
			fill(where+1, where + curr, rest);
			test();
			return;
		}
		//*/
		if (curr == 1) {
			where[1] = to;
			test();
		}
		else {
			if (ans)
				return;
			pmove(curr - 1, from, rest);
			where[curr] = to;
			test();
		}
	}
	else {
		if (ans)
			return;
		move(curr, from, rest);
		///*
		if (from != result[curr] || endp - curr>0) {
			where[curr] = to;
			fill(where, where + curr - 1, from);
			test();
			return;
		}
		//*/
		if (curr == 1) {
			where[1] = to;
			test();
		}
		else {
			if (ans)
				return;
			pmove(curr - 1, to, from);
			where[curr] = to;
			test();
		}
	}
}
inline void pmove(int curr, int from, int to) {
	if (ans)
		return;
	int rest = 3 - from - to;
	bool isnorm = ((from == 0 && to == 1) || (from == 1 && to == 2) || (from == 2 && to == 0));
	///*
	if ( (isnorm && (from != result[curr])) || endp - curr>0 ) {
		where[curr] = to;
		fill(where + 1, where + curr, to);
		test();
		return;
	}
	//*/
	else {
		for (; curr > 0; curr--) {
			if (ans)
				return;
			if (where[curr] != to) {
				//du
				if (ans)
					return;
				move(curr, where[curr], to);
			}
		}
	}
}
int main () {
	//freopen("input.txt", "r", stdin);
	ma['A'] = 0;
	ma['B'] = 1;
	ma['C'] = 2;

	scanf("%d", &testcase);

	for (int t = 1; t <= testcase; t++) {

		scanf("%d", &n);

		endp = n;
		for (int i = 1; i <= n; i++)
		where[i] = 0;

		for (int i = 1; i <= n; i++) {
			scanf("%1c", &c);
			while (c == '\n') {
				scanf("%1c", &c);
			}
			result[i] = ma[c];
		}
		ans = false;
		test();
		pmove(n, 0, 1);
		test();
		if (ans)
			printf("Case #%d\nYES\n", t);
		else
			printf("Case #%d\nNO\n", t);
	}
}