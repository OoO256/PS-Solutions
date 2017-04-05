#include <stdio.h>
#include <algorithm>
using namespace std;

int main () 
{
    
    int n;
    scanf("%d", &n);
    int arr[n];
    int dp[n];
    
    for (int i=0; i<n; i++) 
    {       
        scanf("%d", &arr[i]);
    }
    for (int i=0; i<n; i++) 
    {       
        dp[i]=arr[i];
    }
    
    for (int j=0; j<n; j++) 
    {
        
        for (int k=j+1; k<n; k++) 
        {
            
            if (arr[k]>arr[j]) 
            {
                dp[k]=max(dp[k], dp[j]+arr[k]);
            }
        }
    }
    
    printf("%d", *max_element( dp, dp + n ));
    
    
}