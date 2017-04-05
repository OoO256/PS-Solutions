#include <stack>
#include <stdio.h>
#include <list>

using namespace std;


int main () {
    
    int n;
    scanf("%d", &n);
    stack<int> s;
    list<int> l;
    list<int> ans;
    s.push(0);
    
    for(int i=0; i<n; i++) {
        int para=0;
        scanf("%d", &para);
        l.push_back(para);
    }
    for(int i=1; i<n+1; i++) {
        
        if (s.top()==l.front()) {
            s.pop();
            ans.push_back(0);
            l.pop_front();
            i--;
        }
        else if (i<l.front()) {
            s.push(i);
            ans.push_back(1);
        }
        else if (i==l.front()) {
            //s.push(i);
            ans.push_back(1);
            //s.pop();
            l.pop_front();
            ans.push_back(0);
        }
        else {
            printf("NO");
            return 1;
        }
    }
    
    for (int i=0; i<l.size(); i++) {
        //l.pop();
        ans.push_back(0);
        
    }
    
    for(int i=0; i<2*n; i++) {
        
        if (ans.front()==1) {
            printf("+\n");
            ans.pop_front();
        }
        else {
            printf("-\n");
            ans.pop_front();
        }
        
    }
    
    return 0;
    
}
