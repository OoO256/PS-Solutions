#include <stdio.h>

int max2(int, int);

int main () {
    
    int n;
    scanf("%d", &n);
    
    int price[n+1];
    int dp[n+1];
    
    for (int h=1; h<n+1; h++)
    {
        scanf("%d", &price[h]);
    }
    
    for (int h=1; h<n+1; h++)
    {
        dp[h]=price[h];
    }
    
    for (int j=1; j<n+1; j++)
    {
        for(int i=1; i<=j/2; i++) 
        {
            dp[j]=max2(dp[j], dp[j-i]+dp[i]);
        }
    }
    printf("%d", dp[n]);
}

int max2 (int a, int b) 
{
    if (a>=b) return a;
    else return b;
}
