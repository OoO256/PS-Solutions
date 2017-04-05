#include <stdio.h>

int main () {
    
    long long dp[70];
    int n;
    
    scanf("%d", &n);
    
    int inputs[n];
    
    
    dp[0]=1;
    dp[1]=1;
    dp[2]=2;
    dp[3]=4;
    dp[4]=8;
    
    for(int i=5; i<70; i++) {
        
        dp[i]=2*dp[i-1]-dp[i-5];
    }
    
    for(int j=0; j<n; j++) {
        scanf("%d", &inputs[j]);
    }
    for(int k=0; k<n; k++) {
        printf("%lld\n", dp[inputs[k]]);
    }
    
    
}