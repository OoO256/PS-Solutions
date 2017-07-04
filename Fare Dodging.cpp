/*
this code is a solution of Fare Dodging
from ACM-ICPC > Regionals > Europe > Northwestern European Regional Contest > Benelux Algorithm Programming Contest > BAPC 2013 Preliminaries #F
https://www.acmicpc.net/problem/9323

programer: 이용욱 Yonguk Lee 
email: qjrmsktso2@gmail.com

It takes 44ms, 4732 KB to solve problem

I hope you can learn sth from mine!
*/


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
	float p;

	void init(int a, int b, float c) {
		dist = a;
		dest = b;
		p = c;
	}
};
class path
{
public:
	float min;
	float dist_0; //무임
	float dist_1; //유임
	int dest;

	void init(float a, float b, float c, int d) {
		min=a;
		dist_0=b;
		dist_1=c;
		dest=d;
	}
};
struct compair_path {
	bool operator()(path a, path b) {
		return a.min > b.min;
	}
};

int n_city, n_road, start, endcity, basicprice, price_1, basicfine;
vector<road>edge[205];

float min(float a, float b) {
	if (a < b) return a;
	else return b;
}

void getinput() {
	scanf("%d %d %d %d %d %d %d", &n_city, &n_road, &start, &endcity, &basicprice, &price_1, &basicfine);
	int i_start, i_end, i_dist;
	float  i_p;
	for (int i = 0; i < n_road; i++) {
		scanf("%d %d %f %d", &i_start, &i_end, &i_p, &i_dist);

		road a, b;
		a.init(i_dist, i_end, i_p/100);
		b.init(i_dist, i_start, i_p / 100);
		edge[i_start].push_back(a);
		edge[i_end].push_back(b);
	}
}

float dijkstra() {
	float dist[205][2];//0:무임승차 1:유임승차
	for (int i = 0; i < 205; i++) {
		dist[i][0] = INF;
		dist[i][1] = INF;
	}

	priority_queue<path, vector<path>, compair_path>pq;

	dist[start][0] = 0;
	dist[start][1] = basicprice;
	path pa;
	pa.init(0, 0, basicprice, start);
	pq.push(pa);

	while (!pq.empty()) {
		int curr = pq.top().dest;
		float currdist_0 = pq.top().dist_0;
		float currdist_1 = pq.top().dist_1;
		pq.pop();

		if (currdist_0 != dist[curr][0] ||  currdist_1 != dist[curr][1]) continue;


		for (road next : edge[curr]) {

			float nextdist_0 = min(currdist_0, currdist_1) + (next.dist*price_1 + basicfine)*next.p;
			float nextdist_1 = min(currdist_0 + basicprice, currdist_1) + next.dist*price_1;

			if ( min(nextdist_0, nextdist_1) < min(dist[next.dest][0], dist[next.dest][1]) ) {
					dist[next.dest][0] = min(dist[next.dest][0], nextdist_0);
					dist[next.dest][1] = min(dist[next.dest][1], nextdist_1);
					pa.init(min(dist[next.dest][0], dist[next.dest][1]), dist[next.dest][0], dist[next.dest][1], next.dest);
					pq.push(pa);
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
		printf("%.2f\n", dijkstra());

		for (int i = 0; i < 205; i++)
			edge[i].clear();

	}
	return 0;
}