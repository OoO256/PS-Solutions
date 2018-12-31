#include <algorithm>
#include <vector>
#include <array>
#include <numeric>
#include <iostream>
#include <queue>
using namespace std;

constexpr bool isVisited(const int vis, const int v) {
	return (vis >> v) % 2;
}

constexpr int setVisited(int vis, const int v) {
	return vis |= 1 << v;
}

constexpr int NotVisited(int vis, const int v) {
	return vis &= ~(1 << v);
}

vector<vector<int>>dp;
int adjacency_matrix[16][16];
int n;
int all_visited;

int getDP(const int curr, const int visited) {
	if (dp[curr][visited] != std::numeric_limits<int>::max())
		return dp[curr][visited];

	int& ret = dp[curr][visited];

	if (visited == all_visited)
	{
		return ret = adjacency_matrix[curr][0];
	}

	for (int next = 0; next < n; next++)
	{
		if (!isVisited(visited, next))
		{
			ret = min(ret, getDP(next, setVisited(visited, next)) + adjacency_matrix[curr][next]);
		}
	}

	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n;
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			cin >> adjacency_matrix[i][j];
			if (adjacency_matrix[i][j] == 0)
			{
				adjacency_matrix[i][j] = 1'000'001;
			}
		}
	}

	dp.resize(n, vector<int>(1 << n));

	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < (1<<n); j++)
		{
			dp[i][j] = std::numeric_limits<int>::max();
		}
	}

	for (size_t i = 0; i < n; i++)
	{
		all_visited = setVisited(all_visited, i);
	}

	int ans = numeric_limits<int>::max();
	for (int i = 0; i < n; i++)
	{
		ans = min(ans, getDP(0, setVisited(0, 0)));
	}

	cout << ans << endl;
}
