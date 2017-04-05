#include <stdio.h>
#include <algorithm>
using namespace std;

int min2(int, int);
int min3(int, int, int);

int main () 
{
    
    int n;
    scanf("%d", &n);
    int dp[n];
    
    dp[1]=0;
    
    for (int i=2; i<n+1; i++) 
    {
        if (i%6==0) 
        {
            dp[i]=min3(dp[i/3], dp[i/2], dp[i-1])+1;
        }
        else if (i%3==0)
        {
            dp[i]=min2(dp[i/3], dp[i-1])+1;
        }
        else if (i%2==0)
        {
            dp[i]=min2(dp[i/2], dp[i-1])+1;
        }
        else
        dp[i] = dp[i-1]+1;
    }
    
    printf("%d", dp[n]);
    
    
}

int min2 (int a, int b) 
{
    if (a<=b) return a;
    else return b;
}

int min3 (int a, int b, int c) 
{
    if (a<=b && a<=c) return a;
    else if (b<=a && b<=c) return b;
    else return c;
}