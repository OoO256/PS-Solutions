#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <math.h>
#include <vector>
#include <memory>
#include <algorithm>
#include <stack>
#include <functional>
using namespace std;
typedef pair<int, int>ii;

int n;
class TwoSat
{
public:

	vector<vector<int>>edge;
	vector<int>discover;
	vector<int>sccId;
	stack<int>st;
	vector<int>result;
	int MAX;
	int vertexCounter = 0, sccCounter = 0;

	TwoSat();

	void ConnectEdge(int from, int to) {
		edge[from].push_back(to);
	}

	void Tarjan();
	int Scc(int curr);

	bool IsPossible(void) {
		for (int i = 1; i <= n; i++)
		{
			if (sccId[Idx(i)] == sccId[oppo(Idx(i))])
			{
				return false;
			}
		}
		return true;
	}

	int oppo(int a) {
		if (a % 2)
			return a - 1;
		else
			return a + 1;
	}

	int Idx(int a) {
		if (a > 0)
			return 2*a -2;
		else
			return -2*a - 1;
	}

	void AssignTF();
	void printResult();
};

TwoSat::TwoSat()
{
	MAX = 2 * n;
	edge.resize(MAX);
	discover.resize(MAX, -1);
	sccId.resize(MAX, -1);
	result.resize(MAX/2, -1);

}

void TwoSat::Tarjan() {
	for (int i = 0; i < MAX; i++)
	{
		if (discover[i] == -1)
		{
			Scc(i);
		}
	}
}

int TwoSat::Scc(int curr) {
	int ret = discover[curr] = vertexCounter++;
	st.push(curr);

	for (auto& next : edge[curr])
	{
		if (discover[next] == -1) {
			ret = min(ret, Scc(next));
		}
		else if (discover[next] < discover[curr] && sccId[next] == -1) {
			ret = min(ret, discover[next]);
		}
	}

	if (ret == discover[curr]) {
		int top;
		while (true)
		{
			top = st.top();
			st.pop();

			sccId[top] = sccCounter;
			if (top == curr)
				break;
		}
		sccCounter++;
	}
	return ret;
}

void TwoSat::AssignTF() {
	vector<pair<int, int>>nodes(MAX);
	for (int i = 0; i < MAX; i++)
	{
		nodes[i] = ii(sccId[i], i);
	}
	sort(nodes.begin(), nodes.end());
	reverse(nodes.begin(), nodes.end());

	for (int i = 0; i < MAX; i++)
	{
		int var = nodes[i].second;
		if (result[var/2] == -1)
		{
			result[var / 2] = var % 2;
		}
	}
}

void TwoSat::printResult() {
	for (int i = 0; i < n; i++)
	{
		printf("%d ", result[i]);
	}	
}

int main() {
	int m;
	scanf("%d %d", &n, &m);

	unique_ptr<TwoSat> ts = make_unique<TwoSat>();
	int a, b;
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &a, &b);
		ts->ConnectEdge(ts->oppo(ts->Idx(a)), ts->Idx(b));
		ts->ConnectEdge(ts->oppo(ts->Idx(b)), ts->Idx(a));
	}
	
	ts->Tarjan();

	const bool tsIsPossible = ts->IsPossible();

	printf("%d\n", tsIsPossible);

	if (tsIsPossible)
	{
		ts->AssignTF();
		ts->printResult();
		printf("\n");
	}

	return 0;


}
