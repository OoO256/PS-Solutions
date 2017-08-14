#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
//#include <time.h>
using namespace std;
typedef long long ll;
typedef pair<int, int>ii;
const int INF = (1 << 31)-1;
vector<int> ans;

class edge
{
public:
	int dest;
	//destination node of the edge
	int res;
	//residancial flow of the edge
	int inv;
	//the order of inverse edge in vector of edge of this edge's destination node

	edge(int dest_new, int res_new, int inv_new) {
		dest = dest_new;
		res = res_new;
		inv = inv_new;
	}
};

class networkflow_dinic {
	/*
	this class store graph in graph vector,
	spliting one node into two node.
	the first node is connected with coming edges from other edge
	Ans the second node is connected with edges toward other edge

	the infomation of n th node will be stored at 2n and 2n+1 th element of vector graph
	*/
public:
	int size;
	int source, sink;
	vector<vector<edge> > graph;
	vector<int> depth;
	networkflow_dinic(int n) {
		size = 2*n;		
		depth.resize(size);
		graph.resize(size);
	}
	void connect_edge(int from, int to, int cap, int cap_inv) {
		graph[from].push_back(edge(to, cap, graph[to].size()));
		graph[to].push_back(edge(from, cap_inv, graph[from].size() - 1));
	}
	void getinput(int n, int m) {
		int temp_input;
		
		scanf("%d %d", &source, &sink);
		source = (source - 1) * 2;
		sink = (sink - 1) * 2 + 1;
		for (int i = 0; i < n; i++) {
			scanf("%d", &temp_input);
			connect_edge(i * 2, i * 2 + 1, temp_input, 0);
		}
		int edge_from, edge_to;
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &edge_from, &edge_to);
			edge_from--;
			edge_to--;
			edge_from *= 2;
			edge_to *= 2;
			connect_edge(edge_from + 1, edge_to, INF, 0);
			connect_edge(edge_to + 1, edge_from, INF, 0);
		}


	}
	bool get_depth(vector<ii>& p) {
		vector<bool> vis(size, false);
		queue<int> q;
		depth.assign(size, -1);

		int curr = source;
		vis[source] = true;
		q.push(source);
		depth[source] = 0;

		while (!q.empty())
		{
			curr = q.front();
			q.pop();
			if (curr == sink)
				break;

			for (int i = 0; i < graph[curr].size(); i++) {
				edge next = graph[curr][i];
				if (next.res && !vis[next.dest]) {
					vis[next.dest] = true;
					q.push(next.dest);
					depth[next.dest] = depth[curr] + 1;
					p[next.dest] = ii(curr, i);
				}
			}
		}
		return vis[sink];
	}
	bool flow_blocking_flow() {
		vector<ii> parent(size);
		bool result_get_depth = get_depth(parent);
		if (result_get_depth) {

			int curr = sink, before = -1;
			int block_flow = INF;
			while (curr != source)
			{
				block_flow = min(block_flow, graph [parent[curr].first] [parent[curr].second].res);
				curr = parent[curr].first;
			}

			curr = sink;
			while (curr != source)
			{
				before = parent[curr].first;
				graph[before][parent[curr].second].res -= block_flow;
				graph[curr][graph[before][parent[curr].second].inv].res += block_flow;
				curr = before;
			}

		}
		return result_get_depth;
	}
	void dinic() {
		bool result_flow_blocking;
		do
		{
			result_flow_blocking = flow_blocking_flow();
		} while (result_flow_blocking);
	}
	void find_min_cut() {
		queue<int>q;
		vector<bool> vis(size, false);

		int curr = source;
		vis[source] = true;
		q.push(source);

		while (!q.empty())
		{
			curr = q.front();
			q.pop();

			for (edge next : graph[curr]) {				
				if (next.res && !vis[next.dest]) {
					vis[next.dest] = true;
					q.push(next.dest);
				}
			}
		}

		for (int i = 0; i < size; i += 2) {
			for (edge j : graph[i]) {
				if (j.dest == i + 1 && j.res == 0 && vis[i] && !vis[i + 1]) {
					ans.push_back(i / 2 + 1);
				}
			}
		}
	}
};


int main() {
	//freopen("input.txt", "r", stdin);
	//time_t time_start = clock();
	int n, m;

	scanf("%d %d", &n, &m);

	networkflow_dinic nd(n);
	nd.getinput(n, m);
	nd.dinic();
	nd.find_min_cut();

	sort(ans.begin(), ans.end());
	for (int i : ans)
		printf("%d ",i);

	printf("\n");

	//time_t time_end = clock();

	//printf("the time used : %dms\n", time_end - time_start);
}