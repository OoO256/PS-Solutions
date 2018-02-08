#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <math.h>
#include <vector>
#include <memory>
#include <algorithm>
#include <stack>
using namespace std;
typedef pair<int, int>ii;
vector<vector<ii>>adj;

struct edge
{
	int cost;
	int a, b;
};
vector<edge>edges;

class UnionFind {
public:
	int size;
	vector<int>p;
	vector<int>rank;

	UnionFind(const int n);
	int Find(const int a);
	void Merge(const int a, const int b);
};

UnionFind::UnionFind(const int n) {
	size = n;
	p.resize(size+1, -1);
	rank.resize(size+1, 1);
}

int UnionFind::Find(const int a) {
	int _a = a;
	while (p[_a]>=0)
	{
		_a = p[_a];
	}
	if (a != _a)
		p[a] = _a;
	return _a;
}

void UnionFind::Merge(const int a, const int b) {
    int fa = Find(a), fb = Find(b);
	if (rank[fa]<rank[fb])
	{
		p[fa] = fb;
	}
	else if (rank[fa]>rank[fb])
	{
		p[fb] = fa;
	}
	else
	{
		p[fa] = fb;
		rank[fb]++;
	}
}

int main() {
	int n, m;
	scanf("%d", &n);
	UnionFind uf(n);
	adj.resize(n+1);
	scanf("%d", &m);
	int from, to, cost;
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &from, &to, &cost);
		adj[from].emplace_back(to, cost);
		adj[to].emplace_back(from, cost);
		edges.push_back({ cost, from, to });
	}

	sort(edges.begin(), edges.end()
		, [](const edge a, const edge b) {
		return a.cost < b.cost;
	});


	int ans = 0;
	for_each(edges.begin(), edges.end()
		, [&ans, &uf](const edge e) {
		if (uf.Find(e.a) != uf.Find(e.b))
		{
			//printf("merge %d %d\n", e.a, e.b);
			uf.Merge(e.a, e.b);
			ans += e.cost;
			//printf("ans +=%d\n", e.cost);
		}
	});

	printf("%d\n", ans);
}
