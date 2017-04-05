//solution of Nationwide Internet Competition > Asia Regional - Daejeon Nationalwide Internet Competition 2012 #G
//https://www.acmicpc.net/problem/9012
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

int test() {
    
    int a=0;
    string s="t7";
    getline( cin, s );

    for(int i=0; i<s.size(); i++) {
        
        if (s.at(i)=='(') a++;
        else if (s.at(i)==')') { 
            a--;
            if (a<0) return 0;
            
        }
        
    }
    if (a == 0) return 1;
    else return 0;
}


int main() {
    
    
    int t;
    scanf("%d", &t);
    int ans[t];
    
    for(int i=0; i<t+1; i++) {
        ans[i] = test();
    }
    
    for(int j=1; j<t+1; j++) {
        if (ans[j]==1) printf("YES\n");
        else printf("NO\n");
        
    }
    return 0;
}

