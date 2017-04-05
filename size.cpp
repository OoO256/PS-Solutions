#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

int main() {
    
    string s;
    getline( cin, s );
    
    printf("%d", (int)s.size());
    
    return 0;
}