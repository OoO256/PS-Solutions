#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <functional>
#define INF 999999999
using namespace std;
class road
{
public:
	int dist;
	int dest;
	int p;

	road(int a, int b, int c) {
		dist = a;
		dest = b;
		p = c;
	};
};
class path
{
public:
	int dist_0; //무임
	int dist_1; //유임
	int dest;

	path(int b, int c, int d) {
		dist_0 = b;
		dist_1 = c;
		dest = d;
	};
};
bool operator>(path a, path b) {
	return a.dist_0 > b.dist_0;
}

int n_city, n_road, start, endcity, basicprice, price_1, basicfine;
vector<road>edge[205];


void getinput() {
	scanf("%d %d %d %d %d %d %d", &n_city, &n_road, &start, &endcity, &basicprice, &price_1, &basicfine);
	int i_start, i_end, i_dist;
	int  i_p;
	for (int i = 0; i < n_road; i++) {
		scanf("%d %d %d %d", &i_start, &i_end, &i_p, &i_dist);

		edge[i_start].emplace_back(i_dist, i_end, i_p);
		edge[i_end].emplace_back(i_dist, i_start, i_p);
	}
}

int dijkstra() {
	int dist[205][2];//0:무임승차 1:유임승차
	for (int i = 0; i < 205; i++) {
		dist[i][0] = INF;
		dist[i][1] = INF;
	}

	priority_queue<path, vector<path>, greater<path>>pq;

	dist[start][0] = 0;
	dist[start][1] = basicprice * 100;
	pq.emplace(0, basicprice * 100, start);
	int curr;
	int currdist_0, currdist_1, nextdist_0, nextdist_1;
	while (!pq.empty()) {
		curr = pq.top().dest;
		currdist_0 = pq.top().dist_0;
		currdist_1 = pq.top().dist_1;
		pq.pop();

		if (currdist_0 != dist[curr][0] || currdist_1 != dist[curr][1]) continue;


		for (road next : edge[curr]) {

			nextdist_0 = min(currdist_0, currdist_1) + (next.dist*price_1 + basicfine)*next.p;
			nextdist_1 = min(currdist_0 + basicprice * 100, currdist_1) + next.dist*price_1 * 100;

			if (min(nextdist_0, nextdist_1) < min(dist[next.dest][0], dist[next.dest][1])) {
				dist[next.dest][0] = min(dist[next.dest][0], nextdist_0);
				dist[next.dest][1] = min(dist[next.dest][1], nextdist_1);
				pq.emplace(dist[next.dest][0], dist[next.dest][1], next.dest);
			}
		}
	}
	return min(dist[endcity][0], dist[endcity][1]);
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--)
	{
		getinput();
		printf("%.2f\n", (float)dijkstra() / 100);

		for (int i = 0; i < 205; i++)
			edge[i].clear();

	}
	return 0;
}
