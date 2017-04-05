#include <stdio.h>
#include <algorithm>
using namespace std;

int main () {
    
    int n, k, re=0;
    
    scanf("%d", &n);
    scanf("%d", &k);
    
    int dp[k+1][n];
    int coinprice[n];
    
    for (int i=0; i<n; i++)
    {
        scanf("%d", &coinprice[i]);
    }
    sort(coinprice, coinprice+n);
    
    
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<k+1; j++)
        {
            dp[j][i]=0;
        }
    }
    
    for (int i=0; i<n; i++)
    {
        for (int j=1; j<k+1; j++)
        {
            for (int l=0; l<n; l++)
            {
                if (j%coinprice[l]==0) dp[j][l]=1;
            }
        }
    }
    
    for (int i=1; i<n; i++)
    {
        for (int j=1; j<k+1; j++)
        {
            for (int l=0; l*coinprice[i]<=j; l++)
            {
                dp[j][i] +=dp[j-l*coinprice[i]][i-1];
            }
            //if (j<coinprice[i]) dp[j][i]+=dp[j][i-1];
        }
    }
    
    printf("%d",dp[k][n-1]);
    
    return 0;
}