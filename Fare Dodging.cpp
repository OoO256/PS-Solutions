/*
this code is a solution of Fare Dodging
from ACM-ICPC > Regionals > Europe > Northwestern European Regional Contest > Benelux Algorithm Programming Contest > BAPC 2013 Preliminaries #F
https://www.acmicpc.net/problem/9323

programer: 이용욱 Yonguk Lee 
email: qjrmsktso2@gmail.com

I hope you can learn sth from mine!
*/


#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <functional>
#define INF 999999999
using namespace std;
struct road
{
	int dist;
	int dest;
	float p;
};
road make_road (int a, int b, float c) {
	road r;
	r.dist = a;
	r.dest = b;
	r.p = c;
	return r;
};
struct path
{
	float min;
	float dist_0; //무임
	float dist_1; //유임
	int dest;
};
path make_path(float a, float b, float c, int d) {
	path p;
	p.min=a;
	p.dist_0=b;
	p.dist_1=c;
	p.dest=d;
	return p;
}
struct compair_path {
	bool operator()(path a, path b) {
		return a.min > b.min;
	}
};

int n_city, n_road, start, endcity, basicprice, price_1, basicfine;

float min(float a, float b) {
	if (a < b) return a;
	else return b;
}

void getinput(vector<road> *edge) {
	scanf("%d %d %d %d %d %d %d", &n_city, &n_road, &start, &endcity, &basicprice, &price_1, &basicfine);
	int i_start, i_end, i_dist;
	float  i_p;
	for (int i = 0; i < n_road; i++) {
		scanf("%d %d %f %d", &i_start, &i_end, &i_p, &i_dist);
		edge[i_start].push_back(make_road(i_dist, i_end, i_p / 100));
		edge[i_end].push_back(make_road(i_dist, i_start, i_p / 100));
	}
}

float dijkstra(vector<road> *edge) {
	float dist[205][2];//0:무임승차 1:유임승차
	for (int i = 0; i < 205; i++) {
		dist[i][0] = INF;
		dist[i][1] = INF;
	}
	priority_queue<path, vector<path>, compair_path>pq;
	dist[start][0] = 0;
	dist[start][1] = basicprice;
	pq.push(make_path(0, 0, basicprice, start));

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
					pq.push(make_path(min(dist[next.dest][0], dist[next.dest][1]), dist[next.dest][0], dist[next.dest][1], next.dest));
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
		vector<road>edge[205];
		getinput(edge);
		printf("%.2f\n", dijkstra(edge));
	}
	return 0;
}
