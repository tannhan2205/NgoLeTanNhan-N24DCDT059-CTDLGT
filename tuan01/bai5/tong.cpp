#include<bits/stdc++.h>
using namespace std;
int main() 
{ 
    int n;
    cin >> n;
    long long tong = 0;
    long long solonnhat = LONG_LONG_MIN;
    for (int i=0; i<n; i++)
{
    long long a;
    cin>>a;
    tong += a;
    solonnhat=max(solonnhat, a);
}
    cout << tong << " " << solonnhat<<endl;
    return 0;
}