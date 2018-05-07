#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <memory>
#include <functional>
using namespace std;
typedef pair<int, int> ii;

vector<vector<int>>dp;

enum class TypeOfGraph
{
	unweighted_directed
	, unweighted_undirected
	, weighted_directed
	, weighted_undirected
};

struct next_prev
{
	int next, prev;
	next_prev(int n, int p) : next(n), prev(p) {}
};

class Graph
{
public:
	int size = 0;

	template<typename T>
	vector<vector<T>>adj;

	Graph() {};
	Graph(int _size);
	Graph(int _size, int edge, enum TypeOfGraph tog);

	template<typename Func>
	void BFS(int start, Func F);
};

template<typename T>
Graph::Graph(int _size)
{
	size = _size;
	adj.resize(size);
}

template<typename T>
Graph::Graph(int _size, int edge, enum TypeOfGraph tog) {
	size = _size;
	adj.resize(size);

	int from, to, weight;
	for (int i = 0; i < edge; i++)
	{
		switch (tog)
		{
		case TypeOfGraph::unweighted_directed:
			scanf("%d %d", &from, &to);
			adj[from].emplace_back(to);
			break;
		case TypeOfGraph::unweighted_undirected:
			scanf("%d %d", &from, &to);
			adj[from].emplace_back(to);
			adj[to].emplace_back(from);
			break;
		case TypeOfGraph::weighted_directed:
			scanf("%d %d %d", &from, &to, &weight);
			adj[from].emplace_back(to, weight);
			break;
		case TypeOfGraph::weighted_undirected:
			scanf("%d %d %d", &from, &to, &weight);
			adj[from].emplace_back(to, weight);
			adj[to].emplace_back(from, weight);
			break;
		default:
			break;
		}
	}
}

template<typename Func>
void BFS(int start, Func F) {

	queue<next_prev>q;
	
	for (auto next : adj[start])
	{
		q.emplace(next, start);
	}


	for (int i = 0; i < size; i++)
	{
		dp[start][i] = i + 1;
	}

	while (!q.empty())
	{
		const int curr = q.front().next;
		const int before = q.front().prev;

		for (int i = 0; i < size; i++)
		{
			F();
		}
	}

}


int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	Graph tree(n, m, TypeOfGraph::unweighted_directed);

	dp.resize(n, vector<int>(n));
	const int ROOT = 1;

	tree.BFS(ROOT, [&]() {dp[curr]});


}