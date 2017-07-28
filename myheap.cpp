// heap structure practice
#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>
#include <math.h>
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
	
	T* pointer_heap_operator;
	//비교에 사용할 연산자
	
	vector<int> tree;
	//트리를 구성할 벡터
	
	int size_now;
	//지금의 size


	heap(int size, T* pointer_given_operator) {
		h = ceil(log(size+1) / log(2));
		size_full = 1 << h;
		size_now = 0;
		pointer_heap_operator = pointer_given_operator;
		tree.assign(size_full, BASE);
	};
	//생성자

	void push(int new_element) {
		size_now++;
		tree[size_now] = new_element;
		int index_curr = size_now;
		while (index_curr / 2 >= 1) {
			if ((*pointer_heap_operator)(tree[index_curr/2], tree[index_curr])) {
				//op(부모, 자식)
				//자식보다 부모가 작으면
				swap(tree[index_curr], tree[index_curr / 2]);
			}

			index_curr /= 2;
		}
		
	};
	void pop(void) {
		tree[1] = BASE;
		swap(tree[1], tree[size_now]);
		size_now--;

		int curr = 1;
		while (curr<size_full/2) {
			if ((*pointer_heap_operator)(tree[curr], tree[curr * 2]) || (*pointer_heap_operator)(tree[curr], tree[curr * 2 + 1])) {
				//교체 필수
				if ((*pointer_heap_operator)(tree[curr * 2 + 1], tree[curr * 2]) || tree[curr * 2] == tree[curr * 2 + 1]) {
					swap(tree[curr], tree[curr * 2]);
					curr *= 2;
				}
				else {
					swap(tree[curr], tree[curr * 2 + 1]);
					curr = curr * 2 + 1;
				}
			}
			else {
				//교체 x
				return;
			}
		}
	}

	int top(void) {
		return tree[1];
	};
};

struct struct_operator
{
	bool operator()(int a, int b) {
		//same as >

		return a < b;
	}
};

int main(void) {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	struct_operator myoperator;

	heap<struct_operator> myheap(n, &myoperator);
	//myheap은 가장 큰 원소를 top에 둠
	//인자로 준 펑터가 앞 인자가 더 작은지 확인하는 거라
	//인자(부모, 자식)해서 true면 swap하기 때문에
	//작은 부모는 자식과 스왑됨ㅠㅠ
	//호에에에ㅔ엥 넘모넘모 슬퍼요오
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