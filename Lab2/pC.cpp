#include<iostream>
#include<cmath>
#include<vector>

using namespace std;

bool isPrime(int num)
{
    if(num==1 )
    {
        return false;
    }
    int sq=sqrt(num);
    for(int i=2;i<=sq;i++)
    {
        if(num%i==0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int n,Q;
    cin>>n>>Q;

    vector<int> arr(n);
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }

    while(Q--)
    {
        int opt;
        cin>>opt;
        if(opt==1)
        {
            int loca,val;
            cin>>loca>>val;
            arr[loca-1]=val;
        }
        else if(opt==2)// opt==2
        {
            //find max prime
            int l,r;
            cin>>l>>r;
            int maxP=-1;

            for(int i=l-1;i<r;i++)
            {
                if(isPrime(arr[i]))
                {
                    maxP=max(maxP,arr[i]);
                }
            }

            cout<<maxP<<endl;
        }
    }

    return 0;
}