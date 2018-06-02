// heap structure practice
#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>
#include <cmath>
#include <cassert>
#include <functional>
using namespace std;
const int MAXN = 1000 * 1000;
const int BASE = -1;
int n, x;

template <typename T>
class heap {
public:
	int h;
	//tree의 높이

	int size_full;
	//heap이 full-binary-tree일때 node가 가질 수 있는 가장 큰 index

	using comp_operator = function<bool(T, T)>;
	comp_operator comp;
	//비교에 사용할 연산자

	vector<T> tree;
	//트리를 구성할 벡터

	int size_now;
	//지금의 size


	heap(int size, comp_operator comp)
	{
		h = ceil(log(size + 1) / log(2));
		size_full = 1 << h;
		size_now = 0;
		this->comp = comp;
		tree.resize(size_full, BASE);
	};
	//생성자

	void push(T new_element) {
		size_now++;
		tree[size_now] = new_element;
		int index_curr = size_now;
		while (index_curr / 2 >= 1) {
			if (comp(tree[index_curr / 2], tree[index_curr])) {
				//op(부모, 자식)
				//자식보다 부모가 작으면
				swap(tree[index_curr], tree[index_curr / 2]);
			}
			index_curr /= 2;
		}

	};

	T pop(void) {
		assert(tree[1] != BASE && "heap is empty!\n");
		return tree[1];
		tree[1] = BASE;
		swap(tree[1], tree[size_now]);
		size_now--;

		int curr = 1;
		while (curr < size_full / 2
			&& (comp(tree[curr], tree[curr * 2]) 
				|| comp(tree[curr], tree[curr * 2 + 1]))
			) {
			//교체 필수
			if (comp(tree[curr * 2 + 1], tree[curr * 2]) 
				|| tree[curr * 2] == tree[curr * 2 + 1]) {
				swap(tree[curr], tree[curr * 2]);
				curr *= 2;
			}
			else {
				swap(tree[curr], tree[curr * 2 + 1]);
				curr = curr * 2 + 1;
			}
		}
	}

	T top(void) {
		return tree[1];
	};
};

int main(void) {
	//freopen("input.txt", "r", stdin);
	scanf("%d", &n);

	auto int_smaller = [](const int lhs, const int rhs) { return lhs < rhs; };
	heap<int> myheap(n, int_smaller);
	//myheap은 가장 큰 원소를 top에 둠
	//인자로 준 펑터가 앞 인자가 더 작은지 확인하는 거라
	//인자(부모, 자식)해서 true면 swap하기 때문에
	//작은 부모는 자식과 스왑됨ㅠㅠ
	//there is biggest element at top
	int temp;
	while (n--)
	{
		scanf("%d", &x);
		if (x == 0) {
			if (myheap.size_now == 0) {
				printf("0\n");
			}
			else {
				temp = myheap.top();
				myheap.pop();
				printf("%d\n", temp);
			}
		}
		else {
			myheap.push(x);
		}
	}

	return 0;
}
