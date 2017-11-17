#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <queue>
using namespace std;
const int INF = 987654321;
const int MOD = 10 * 1000 * 1000;
typedef pair<int, int>ii;

int cache[105][105];
int poly(int ceil, int n) {
	int& ret = cache[n][ceil];
	if (ceil == n)
		return ret = 1;
	if (ret != -1)
		return ret;


	ret = 0;
	for (size_t i = 1; i <= n - ceil; i++)
	{
		ret += poly(i, n - ceil)*(ceil + i - 1);
		ret %= MOD;
	}
	return ret%MOD;
}

int main() {
	int testcase;
	scanf("%d", &testcase);
	fill(&cache[0][0], &cache[105][105], -1);
	while (testcase--)
	{
		int n, ans = 0;
		scanf("%d", &n);
		for (size_t i = 1; i <= n; i++)
		{
			ans += poly(i, n);
			ans %= MOD;
		}
		printf("%d\n", ans);
	}
	return 0;
}