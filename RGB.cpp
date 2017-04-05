#include <stdio.h>

int min2(int, int);
int min3(int, int, int);

int main () {
    
    int n=0;
    scanf("%d",  &n);
    
    int arr[n][3];
    int dp[n][3];
    
    for (int i=0; i<n; i++) 
    {
        scanf("%d", &arr[i][0]);
        scanf("%d", &arr[i][1]);
        scanf("%d", &arr[i][2]);
    }
    
    dp[0][0]=arr[0][0];
    dp[0][1]=arr[0][1];
    dp[0][2]=arr[0][2];
    
    for (int j=1; j<n; j++) 
    {
        dp[j][0]=min2(dp[j-1][1], dp[j-1][2]) + arr[j][0];
        dp[j][1]=min2(dp[j-1][0], dp[j-1][2]) + arr[j][1];
        dp[j][2]=min2(dp[j-1][0], dp[j-1][1]) + arr[j][2];
        
    }
    
    printf("%d", min3(dp[n-1][0], dp[n-1][1], dp[n-1][2]));
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