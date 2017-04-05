#include <stdio.h>
#include <stack>
#include <string>
#include <iostream>
using namespace std;

int main () {
    
    int result=0;
    string data;
    stack<int> s;
    
    getline( cin, data);
    
    while (data.find("()") != string::npos) {
        data.at((int)data.find("()"))='*';
    }
    
    int n=data.size();
    
    for(int i=0; i<n; i++) {
    if(data.at(i)=='(') {
        s.push(1);
    }
    else if (data.at(i)==')') {
        s.pop();
        result++;
    }
    else {
        result += s.size();
        i++;
    }
    }
    
    printf("%d", result);
    return 0;
}