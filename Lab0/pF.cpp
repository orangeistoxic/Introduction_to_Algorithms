#include<iostream>
#include<algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n,q;
    long long sum=0;
    cin>>n>>q;

    long long *arr = new long long[n];
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
        sum+=arr[i];
    }

    while(q--)
    {
        int l;
        long long r;
        cin>>l>>r;
        sum-=arr[l-1];
        arr[l-1]=r;
        sum+=r;
        cout<<sum<<endl;
    }

    return 0;
}