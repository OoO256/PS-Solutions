// heap structure practice
#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>
#include <functional>
#include <cmath>

template <typename T, typename Op = std::less<T>>
class heap {
  enum { BASE = -1 };

  //tree의 높이
  int h;  

  //heap이 full-binary-tree일때 node가 가질 수 있는 가장 큰 index
  int size_full; 
  
  //비교에 사용할 연산자
  Op op;
  
  //트리를 구성할 벡터
  std::vector<T> tree;
  
  //지금의 size
  int size_now;

public:
  heap(int size, Op oper = Op{}) : op(oper) {
    h = ceil(log(size+1) / log(2));
    size_full = 1 << h;
    size_now = 0;
    tree.assign(size_full, BASE);
  }

  void push(int new_element) {
    size_now++;
    tree[size_now] = new_element;
    int index_curr = size_now;
    while (index_curr / 2 >= 1) {
      if (op(tree[index_curr/2], tree[index_curr])) {
        //op(부모, 자식)
        //자식보다 부모가 작으면
        std::swap(tree[index_curr], tree[index_curr / 2]);
      }

      index_curr /= 2;
    }
    
  }

  void pop(void) {
    tree[1] = BASE;
    std::swap(tree[1], tree[size_now]);
    size_now--;

    int curr = 1;
    while (curr<size_full/2) {
      if (op(tree[curr], tree[curr * 2]) || op(tree[curr], tree[curr * 2 + 1])) {
        //교체 필수
        if (op(tree[curr * 2 + 1], tree[curr * 2]) || tree[curr * 2] == tree[curr * 2 + 1]) {
          std::swap(tree[curr], tree[curr * 2]);
          curr *= 2;
        }
        else {
          std::swap(tree[curr], tree[curr * 2 + 1]);
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
  }

  int size() {
    return size_now;
  }
};

int main(void) {
  int n, x;
  //freopen("input.txt", "r", stdin);
  scanf("%d", &n);

  heap<int> myheap(n);
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
      if (myheap.size() == 0) {
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
