#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <math.h>
#include <vector>
#include <memory>
#include <algorithm>
#include <stack>
using namespace std;

int n;
class TwoSat
{
public:

	vector<vector<int>>edge;
	vector<int>discover;
	vector<int>sccId;
	stack<int>st;
	int size;
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
			if (sccId[i] == sccId[i + n])
			{
				return false;
			}
		}
		return true;
	}

	int oppo(int a) {
		if (a > n)
		{
			return a - n;
		}
		else {
			return a + n;
		}
	}

	int Idx(int a) {
		if (a > 0)
			return a;
		else
			return -a + n;
	}
};

TwoSat::TwoSat()
{
	size = 2 * n;
	edge.resize(size + 1);
	discover.resize(size + 1, -1);
	sccId.resize(size + 1, -1);

}

void TwoSat::Tarjan() {
	for (int i = 1; i <= n; i++)
	{
		if (discover[i] == -1)
		{
			Scc(i);
		}
	}

	for (int i = 1; i <= n; i++)
	{
		if (discover[i + n] == -1)
		{
			Scc(i + n);
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

	printf("%d\n", ts->IsPossible());

	return 0;


}