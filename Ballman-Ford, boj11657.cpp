#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;
typedef pair<int, int> ii;

vector<vector<ii>>edge;
vector<int>dist;

void getInput(const int& n, const int& m) {
	edge.resize(n + 1);
	int from, to, cost;
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &from, &to, &cost);
		edge[from - 1].emplace_back(to - 1, cost);
		//edge[to - 1].emplace_back(from - 1, cost);
	}
}

bool ballmanFord(const int& start, const int & n) {
	dist.resize(n, INT32_MAX);
	const int MAX_PATH = n - 1;

	dist[start] = 0;
	for (int pathCount = 0; pathCount < MAX_PATH; pathCount++)
	{
		for (int curr = 0; curr < n; curr++)
		{
			for (ii& next : edge[curr])
			{
				if (dist[curr] != INT32_MAX && dist[next.first] > dist[curr] + next.second)
				{
					dist[next.first] = dist[curr] + next.second;
				}
			}
		}
	}
	for (int curr = 0; curr < n; curr++)
	{
		for (ii& next : edge[curr])
		{
			if (dist[next.first] != INT32_MAX && dist[next.first] > dist[curr] + next.second)
			{
				return true;
			}
		}
	}
	return false;
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	getInput(n, m);

	bool isCycle = ballmanFord(0, n);
	if (isCycle)
	{
		printf("-1\n");
		return 0;
	}
	else {
		for (int i = 1; i < n; i++) {
			if (dist[i] == INT32_MAX)
			{
				printf("-1\n");
			}
			else
			{
				printf("%d\n", dist[i]);
			}
		}
	}
}