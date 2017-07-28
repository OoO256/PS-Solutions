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
	//tree�� ����

	int size_full; 
	//heap�� full-binary-tree�϶� node�� ���� �� �ִ� ���� ū index
	
	T* pointer_heap_operator;
	//�񱳿� ����� ������
	
	vector<int> tree;
	//Ʈ���� ������ ����
	
	int size_now;
	//������ size


	heap(int size, T* pointer_given_operator) {
		h = ceil(log(size+1) / log(2));
		size_full = 1 << h;
		size_now = 0;
		pointer_heap_operator = pointer_given_operator;
		tree.assign(size_full, BASE);
	};
	//������

	void push(int new_element) {
		size_now++;
		tree[size_now] = new_element;
		int index_curr = size_now;
		while (index_curr / 2 >= 1) {
			if ((*pointer_heap_operator)(tree[index_curr/2], tree[index_curr])) {
				//op(�θ�, �ڽ�)
				//�ڽĺ��� �θ� ������
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
				//��ü �ʼ�
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
				//��ü x
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
	//myheap�� ���� ū ���Ҹ� top�� ��
	//���ڷ� �� ���Ͱ� �� ���ڰ� �� ������ Ȯ���ϴ� �Ŷ�
	//����(�θ�, �ڽ�)�ؼ� true�� swap�ϱ� ������
	//���� �θ�� �ڽİ� ���ҵʤФ�
	//ȣ�������Ŀ� �Ѹ�Ѹ� ���ۿ��
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