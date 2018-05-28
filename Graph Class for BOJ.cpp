#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <memory>
#include <functional>
#include <limits>
using namespace std;
typedef pair<int, int> ii;
using ll = long long;
const int MOD = 1'000'000'007;

template<typename ConcreteGraph>
class Graph {
public:
	int size = 0, edge = 0;

	int dijkstra(int start, int end) {
		static_cast<ConcreteGraph>(this)->dijkstra(start, end);
	}
private:
	Graph() = default;
	Graph(int size) : size(size) {}
	Graph(int size, int edge) : size(size), edge(edge) {}
	friend ConcreteGraph;
};

template<typename T>
class WeightedGraph : Graph<WeightedGraph<T>> {
public:
	vector<vector<pair<T, T>>> adj;

	WeightedGraph(int size)
		: Graph<WeightedGraph<T>>(size), adj(size) {}

	WeightedGraph(int size, int edge)
		: Graph<WeightedGraph<T>>(size, edge), adj(size) {}

	WeightedGraph& getinput_directed(int edge) {
		T from, to, weight;
		for (int i = 0; i < edge; i++) {
			cin >> from >> to >> weight;
			adj[from].emplace_back(to, weight);
		}
		return *this;

	}

	WeightedGraph& getinput_undirected(int edge) {
		T from, to, weight;
		for (int i = 0; i < edge; i++) {
			cin >> from >> to >> weight;
			adj[from].emplace_back(to, weight);
			adj[to].emplace_back(from, weight);
		}
		return *this;
	}
};

template<typename T>
class UnweightedGraph : Graph<UnweightedGraph<T>> {
public:
	vector<vector<T>> adj;

	UnweightedGraph(int size)
		: Graph<UnweightedGraph<T>>(size), adj(size) {}

	UnweightedGraph(int size, int edge)
		: Graph<UnweightedGraph<T>>(size, edge), adj(size) {}

	UnweightedGraph& getinput_directed(int edge) {
		T from, to;
		for (int i = 0; i < edge; i++) {
			cin >> from >> to;
			adj[from].push_back(to);
		}
		return *this;
	}

	UnweightedGraph& getinput_undirected(int edge) {
		T from, to;
		for (int i = 0; i < edge; i++) {
			cin >> from >> to;
			adj[from].push_back(to);
			adj[to].push_back(from);
		}
		return *this;
	}
};

template<typename T>
ll getDP(UnweightedGraph<T> const& tree,
	const int CURR, const int K,
	vector<vector<ll>>& dp,
	vector<bool>& vis
) {

	if (dp[CURR][K] != -1) {
		return dp[CURR][K];
	}

	vector<int>child;
	child.reserve(tree.adj[CURR].size());
	int unVisitedChildCnt = 0;
	for (const int c : tree.adj[CURR]) {
		if (vis[c] == false) {
			child.push_back(c);
			unVisitedChildCnt++;
		}
	}

	if (unVisitedChildCnt == 0) {
		if (K > 1) {
			return 0;
		}
		else {
			return 1;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n, k;
	cin >> n >> k;

	UnweightedGraph<int>tree(n + 1, n - 1);
	tree.getinput_undirected(n - 1);

	vector<vector<ll>>dp(n + 1, vector<ll>(k, 0));
	vector<bool>vis(n + 1, false);
	cout << getDP(tree, 1, k, dp, vis);
}
