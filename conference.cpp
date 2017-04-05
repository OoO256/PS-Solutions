#include <stdio.h>
#include <algorithm>
#include <vector> 
using namespace std;

int main () {
    
    int n;
    int now=0, c=0;
    
    
    scanf("%d", &n);
    
    vector<pair<int, int> > v(n); //<end, start>
    
    for (int i=0; i<n; i++)
    {
        scanf("%d", &v[i].second);
        scanf("%d", &v[i].first);
    }
    
    sort(v.begin(), v.end());
    
    now=v[0].first;
    c++;
    
    for (int j=0; j<n; j++)
    {
        if(v[j].second>=now)
        {
            now=v[j].first;
            c++;
        }
    }
    
    printf("%d", c);
    
    
    
    
    
    
    
    
    
    
}