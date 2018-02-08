#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int f(int x) {
	return x%5 ? 0 : 1 + f(x / 5);
}

int main() {

	int m;
	scanf("%d", &m);

	for  (int i = 5;;i+=5)
	{
		m -= f(i);

		if (m == 0) {
			printf("%d\n", i);
				return 0;
		}
		else if(m<0)
		{
			printf("-1\n");
			return 0;
		}
	}






}
