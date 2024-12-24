#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>

using namespace std;

void SieveOfEratosthenes(vector<bool> &isPrime)
{
    isPrime[0]=false;
    isPrime[1]=false;
    for(int i=2;i*i<=isPrime.size()-1;i++)
    {
        if(isPrime[i])
        {
            for(int j=i*i;j<=isPrime.size()-1;j+=i)
            {
                isPrime[j]=false;
            }
        }
    }
}

void SegmentTree(vector<int> &arr,vector<int> &sTree)
{
    for(int i=0;i<arr.size();i++)
    {
        sTree[sTree.size()/2+i-1]=arr[i];
    }
    for(int i=sTree.size()/2-2;i>=0;i--)
    {
        sTree[i]=max(sTree[2*i+1],sTree[2*i+2]);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int n,Q;
    cin>>n>>Q;

    vector<bool> isPrime(1000001, true);
    SieveOfEratosthenes(isPrime);
    //cout<<"Sieve done"<<endl;

    vector<int> arr(n, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        if(!isPrime[arr[i]])
        {
            arr[i]=-1;
        }

        
    }
    //cout<<"Input done"<<endl;

    int nextPowOf2=1;
    while(nextPowOf2<n)
    {
        nextPowOf2*=2;
    }
    vector<int> sTree(2*nextPowOf2,-1);
    SegmentTree(arr,sTree); 
    //cout<<"Segment Tree done"<<endl;

    while(Q--)
    {
        int opt;
        cin>>opt;

        if(opt==1)
        {
            int loca,val;
            cin>>loca>>val;
            if(isPrime[val])
            {
                sTree[sTree.size()/2+loca-2]=val;
            }
            else
            {
                sTree[sTree.size()/2+loca-2]=-1;
            }
            int posi=sTree.size()/2+loca-2;
            posi=(posi-1)/2;
            while(posi>0)
            {
                if(posi==0)
                {
                    sTree[posi]=max(sTree[1],sTree[2]);
                    break;
                }
                sTree[posi]=max(sTree[2*posi+1],sTree[2*posi+2]);
                posi=(posi-1)/2;
            }
           
        }
        else //opt==2
        {
            int l,r;
            cin>>l>>r;
            int maxP=-1;
            l=sTree.size()/2+l-2;
            r=sTree.size()/2+r-2;
            while(l<=r)
            {
                if(l==r)
                {
                    maxP=max(maxP,sTree[l]);
                    break;
                }
                if(l%2==0)
                {
                    maxP=max(maxP,sTree[l]);
                    l++;
                }
                if(r%2==1)
                {
                    maxP=max(maxP,sTree[r]);
                    r--;
                }
                l=(l-1)/2;
                r=(r-1)/2;
            }


            cout<<maxP<<endl;
        }
    }

    return 0;
}