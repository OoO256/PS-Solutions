#include <iostream>
#include <algorithm>
#include <vector>
#include <assert.h>
#include <queue>
#include <stack>
using namespace std;
int cloneNum = 0, towerNum = 0;
int height = 0, width = 0;

enum GroundInfo
{
	GROUND = -1,
	CLONE = -2,
	WALL = -3
	// towers will be represented to non-negative int, 0 ~ towerNum
};

enum Dir
{
	RIGHT = 0, UP, LEFT, DOWN
	// towers will be represented to non-negative int, 0 ~ towerNum
};

vector<vector<int>>field;
const int d1[4] = { 0, -1, 0, 1 };
const int d2[4] = { 1, 0, -1, 0 };
const int NOT[4] = { 2, 3, 0, 1 };

int Not(int x) {
	return (x / 4) * 4 + NOT[x % 4];
}

class graph
{
public:
	int size = 0;
	int MAX;
	vector<vector<int>>adj;
	vector<bool>val;

	vector<int>discover;
	vector<int>sccId;
	stack<int>st;
	vector<int>result;
	int vertexCounter = 0, sccCounter = 0;

	graph() {};
	void resize(int size);
	void connectNode(const int rhs, const int lhs);
	void orOperation(const int x1, const int d1, const int x2, const int d2);
	void notOperation(const int x, const int d);

	void AssignTF();
	void printResult();
	void Tarjan();
	int Scc(int curr);
};

void graph::resize(int _size)
{
	size = _size;
	adj.resize(size * 4);
	val.resize(size * 4, false);

	MAX = size * 4;
	discover.resize(size * 4, -1);
	sccId.resize(size * 4, -1);
	result.resize(size, -1);

}

void graph::Tarjan() {
	for (int i = 0; i < size * 4; i++)
	{
		if (discover[i] == -1)
		{
			Scc(i);
		}
	}
}

int graph::Scc(int curr) {
	int ret = discover[curr] = vertexCounter++;
	st.push(curr);

	for (auto& next : adj[curr])
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

void graph::AssignTF() {

	vector<pair<int, int>>nodes(size * 4);
	for (int i = 0; i < MAX; i++)
	{
		nodes[i] = { sccId[i], i };
	}
	sort(nodes.begin(), nodes.end());
	reverse(nodes.begin(), nodes.end());
	

	for (pair<int, int> n : nodes)
	{
		if (!val[n.second] && !val[Not(n.second)])
		{
			val[n.second] = false;
			val[Not(n.second)] = true;
		}
	}
}

void graph::printResult() {
	for (int i = 0; i < size * 4; i += 4)
	{
		const int tVal = val[i] + val[i + 1] * 2 + val[i + 2] * 4 + val[i + 3] * 8;
		if (tVal == 12) {
			result[i / 4] = 1;
		}
		else if (tVal == 9) {
			result[i / 4] = 2;
		}
		else if (tVal == 3) {
			result[i / 4] = 3;
		}
		else if (tVal == 6) {
			result[i / 4] = 4;
		}
		else {
			printf("val 배열에 4개 말고 딴거 묻음요ㅠㅠ");
		}
	}
	int k = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (field[i][j] >= 0)
			{
				cout << result[k];
				k++;
			}
			else
			{
				switch (field[i][j])
				{
				case(GROUND):
					cout << '.';
					break;
				case(CLONE):
					cout << 'n';
					break; 
				case(WALL):
					cout << '#';
					break;
				default:
					break;
				}
			}
			
		}
		cout << endl;
	}
}


void graph::connectNode(const int rhs, const int lhs) {
	adj[rhs].push_back(lhs);
}

void graph::orOperation(const int x1, const int d1, const int x2, const int d2) {

	const int i1 = x1 * 4 + d1;
	const int ni1 = x1 * 4 + NOT[d1];

	const int i2 = x2 * 4 + d2;
	const int ni2 = x2 * 4 + NOT[d2];


	
	//printf("oroper : %d or %d\n", i1, i2);
	connectNode(ni1, i2);
	if (i1 != i2)
		connectNode(ni2, i1);
}

void graph::notOperation(const int x, const int d) {

	const int i = x * 4 + d;
	const int ni = x * 4 + NOT[d];

	//printf("notoper : %d\n", i);
	connectNode(i, ni);
}



graph g;


void getInput() {
	ios_base::sync_with_stdio(false);
	cin >> height >> width;

	field.resize(height, vector<int>(width, GroundInfo::GROUND));


	char input;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			cin >> input;

			if (input == 'n')
			{
				field[i][j] = GroundInfo::CLONE;
				cloneNum++;
			}
			else if (input == 'T')
			{
				field[i][j] = towerNum;
				towerNum++;
			}
			else if (input == '#')
			{
				field[i][j] = GroundInfo::WALL;
			}
			else
			{
				assert(input == '.' && "field input 에 개소리 있음");
			}
		}
	}

	g.resize(towerNum);
}

bool isVaildPos(int i, int j) {
	return 0 <= i
		&& i < height
		&& 0 <= j
		&& j < width;
}

int linearSearch(int i, int j, enum Dir dir) {
	assert(isVaildPos(i, j) && "개소리2");

	while (isVaildPos(i + d1[dir], j + d2[dir]))
	{

		const int next = field[i + d1[dir]][j + d2[dir]];
		if (next >= 0)
		{
			return next;
		}
		else if (next == GroundInfo::WALL)
		{
			return -1;
		}
		else
		{
			// clone, ground
			i += d1[dir];
			j += d2[dir];
		}
	}
	return -1;
}

bool linearSearchFromTower(int i, int j, enum Dir dir) {
	assert(isVaildPos(i, j) && "개소리2");

	while (isVaildPos(i + d1[dir], j + d2[dir]))
	{

		const int next = field[i + d1[dir]][j + d2[dir]];
		if (next >= 0)
		{
			return true;
		}
		else if (next == GroundInfo::WALL || next == GroundInfo::CLONE)
		{
			return false;
		}
		else
		{
			i += d1[dir];
			j += d2[dir];
		}
	}
	return false;
}

void searchTowerFromClone() {
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (field[i][j] == GroundInfo::CLONE) {

				vector<int>T;
				// index of tower and, dir that tower should choose

				int whatSearchedCnt = 0;
				for (int d = 0; d < 4; d++)
				{
					T.push_back(linearSearch(i, j, (Dir)d));
				}

				if (T[0] != -1 && T[2] != -1)
				{
					g.notOperation(T[0], 2);
					g.notOperation(T[2], 0);
					T[0] = -1;
					T[2] = -1;
					

				}

				if (T[1] != -1 && T[3] != -1)
				{
					g.notOperation(T[1], 3);
					g.notOperation(T[3], 1);
					T[1] = -1;
					T[3] = -1;					
				}

				int tCnt = 0;
				pair<int, int>t[2];
				for (int d = 0; d < 4; d++)
				{
					if (T[d] != -1)
					{
						t[tCnt] = pair<int, int>(T[d], NOT[d]);
						tCnt++;
					}
				}

				if (tCnt == 1)
				{
					g.orOperation(t[0].first, t[0].second, t[0].first, t[0].second);
				}
				else if (tCnt == 2)
				{
					g.orOperation(t[0].first, t[0].second, t[1].first, t[1].second);
				}
				else
				{
					assert(false && "시발");
				}


			}
		}
	}
}

void searchTowerFromTower() {
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (field[i][j] >= 0) {
				for (int d = 0; d < 4; d++)
				{
					if (linearSearchFromTower(i, j, (Dir)d)) {
						g.notOperation(field[i][j], d);
					}
				}

			}
		}
	}
}


int main() {

	getInput();
	searchTowerFromClone();
	searchTowerFromTower();
	g.Tarjan();
	g.AssignTF();
	g.printResult();

	return 0;
}