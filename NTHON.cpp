#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <functional>
#include <stdlib.h>
using namespace std;
typedef pair<int, int>ii;
priority_queue<ii, vector<ii>, greater<ii>>pq;
const int INF = 987654321;


int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--)
	{
		int n;
		scanf("%d", &n);
		vector<ii>matchs(n);
		int MAXDIFF = -INF;
		int MINDIFF = INF;
		int* dist;
		for (int i = 0; i<n; i++)
		{
			scanf("%d %d", &matchs[i].first, &matchs[i].second);
			MAXDIFF = max(MAXDIFF, matchs[i].first - matchs[i].second);
			MINDIFF = min(MINDIFF, matchs[i].first - matchs[i].second);

		}

		dist = (int *)calloc(MAXDIFF + 1 - MINDIFF, sizeof(int));
		fill(dist, dist + MAXDIFF + 1 - MINDIFF, INF);

		dist[0 - MINDIFF] = 0;
		pq.push(ii(0, 0 - MINDIFF));
		while (!pq.empty())
		{
			int curr, currdist;
			curr = pq.top().second;
			currdist = pq.top().first;
			pq.pop();

			if (currdist != dist[curr])
				continue;

			for (auto& next : matchs)
			{
				if (curr + next.first - next.second == 0 - MINDIFF
					&& dist[0 - MINDIFF] == 0) {

					dist[curr + next.first - next.second] = currdist + next.first;
					pq.push(ii(currdist + next.first, curr + next.first - next.second));
				}
				else if (0 <= curr + next.first - next.second
						&& curr + next.first - next.second <= MAXDIFF - MINDIFF
						&& dist[curr + next.first - next.second] > currdist + next.first
						) {

						dist[curr + next.first - next.second] = currdist + next.first;
						pq.push(ii(currdist + next.first, curr + next.first - next.second));
					}
				}
				
			}
		if (dist[0 - MINDIFF] == 0)
			printf("IMPOSSIIBLE\n");
		else
			printf("%d\n", dist[0 - MINDIFF]);

		}


	

	return 0;
}