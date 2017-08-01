#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#define INF 999999999
#define xx first
#define yy second
using namespace std;
typedef long long int lli;
typedef pair<int, int> ii;
const int BASE = 0;
int testcase, n;
lli ans = 0;
int dotx, doty;
vector<ii>dots;
vector<int>tree;
class segtree
{
public:
	int size_full;
	segtree(int n) {
		int h = (int)ceil(log(n) / log(2));
		size_full = (1 << (h + 1));
		tree.clear();
		tree.assign(size_full, BASE);
	};
	//»ý¼ºÀÚ
	void update(int index, int diff) {
		int node = index + size_full / 2;
		tree[node] += diff;
		node /= 2;
		while (node != 0) {
			tree[node] = tree[node * 2] + tree[node * 2 + 1];
			node /= 2;
		}
	};

	int sum(int node, int left, int right, int start, int end) {
		if (right < start || end < left)
			return BASE;
		if (left <= start && end <= right)
			return tree[node];
		int mid = (start + end) / 2;
		return sum(node * 2, left, right, start, mid) + sum(node * 2 + 1, left, right, mid + 1, end);
	};

};

void getinput() {
	scanf("%d", &n);

	dots.reserve(n + 5);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &dotx, &doty);
		dots.push_back(ii(dotx, doty));
	}
}

struct cmp_bigx_smally
{
	bool operator()(ii a, ii b) {
		if (a.xx != b.xx)
			return a.xx > b.xx;
		else
			return a.yy < b.yy;
	}
};

struct cmp_bigy
{
	bool operator()(ii a, ii b) {
		return a.yy < b.yy;
	}
};

void init() {
	dots.clear();
	ans = 0;
}

int main() {
	//freopen("input.txt", "r", stdin);
	scanf("%d", &testcase);
	cmp_bigx_smally cmp_xy;
	cmp_bigy cmp_y;

	while (testcase--) {
		getinput();

		stable_sort(dots.begin(), dots.end(), cmp_y);

		int newy = 0, exy = dots[0].yy;
		for (int i = 0; i < n; i++) {
			if (i>0 && dots[i].yy != exy) newy++;
			exy = dots[i].yy;
			dots[i].yy = newy;
		}

		sort(dots.begin(), dots.end(), cmp_xy);
		segtree mysegtree(newy + 1);

		for (ii dot : dots) {
			ans += mysegtree.sum(1, 0, dot.yy, 0, mysegtree.size_full / 2 - 1);
			mysegtree.update(dot.yy, 1);
		}

		printf("%lld\n", ans);

		init();
	}
}