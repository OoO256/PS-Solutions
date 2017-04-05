//this is solution of the problem ; https://www.acmicpc.net/problem/4948
//pnum means prime number

#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

vector<int> pnumlist;
vector<int> answerlist;

int isitpnum(int i) {
    
    for(int j=0;;j++) {
        if (pnumlist[j] <= sqrt(i)) {
            if (i%pnumlist[j]==0) {
                return 0;
            }
        }
        else return 1;
        
    }
    
}

int calpnum(int n) {
    
    int pnum=0;
    
    for (int i=2; i<=n; i++) {
        if (isitpnum(i) == 1 && pnumlist.back() < i) {
            pnumlist.push_back(i);
        }
    }
    
    for (int i=n+1; i<=2*n; i++) {
        if (isitpnum(i)==1) {
            pnum++;
        }
    }
    
    return pnum;
}

int printanswer() {
    
    for(int i=0;i<answerlist.size();i++) {
        printf("%d\n", answerlist[i]);
    }
    return 0;
}

int main() {
    
    int n;
    pnumlist.push_back(2);
    
    while(1) {
        
    n=0;
    scanf("%d", &n);
    if (n==0) break;
    else answerlist.push_back(calpnum(n));
    }
    
    printanswer();
    return 0;
}

