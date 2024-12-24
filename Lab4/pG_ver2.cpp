#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>

using namespace std;

using ll = long long;

const ll MOD = 998244353;

void FindAllnx1(vector<ll> &Allnx1, int crt, int n, bool lastOne, ll state, unordered_map<ll, ll> &AllNeighborConstraint, unordered_map<ll, vector<ll>> &AllNeighbor)
{
    if(crt == n)
    {
        return;
    }

    if(lastOne)
    {
        FindAllnx1(Allnx1, crt+1, n, 0, state, AllNeighborConstraint, AllNeighbor);
    }
    else
    {
        FindAllnx1(Allnx1, crt+1, n, 0, state, AllNeighborConstraint, AllNeighbor);


        ll newState = (state | (1<<crt));
        Allnx1.emplace_back(newState);
        


        ll newneighbourConstraint = newState;

        if (newState & (1 << 0))
        {
            newneighbourConstraint |= (1 << 1);
        }

        if (newState & (1 << (n - 1)))
        {
            newneighbourConstraint |= (1 << (n - 2));
        }

        for (int j = 1; j < n - 1; j++)
        {
            if (newState & (1 << j))
            {
                newneighbourConstraint |= (1 << (j - 1));
                newneighbourConstraint |= (1 << (j + 1));
            }
        }

        AllNeighborConstraint[newState] = newneighbourConstraint;

        for(auto &mask : Allnx1)
        {
            if(!(mask & newneighbourConstraint))
            {
                AllNeighbor[newState].emplace_back(mask);
                AllNeighbor[mask].emplace_back(newState);
            }
        }

        FindAllnx1(Allnx1, crt+1, n, 1, newState, AllNeighborConstraint, AllNeighbor);

        
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin>>n>>k;

    vector<ll> obstical(n, 0);
    for(int i = 0; i < k; i++)
    {
        int x, y;
        cin>>x>>y;
        x--;y--;

        obstical[x] |= (1<<y);
    }

    vector<ll> Allnx1;
    Allnx1.reserve(1<<n);
    Allnx1.emplace_back(0);
    unordered_map<ll, ll> AllNeighborConstraint;
    AllNeighborConstraint.reserve(1<<n);
    AllNeighborConstraint[0] = 0;

    unordered_map<ll, vector<ll>> AllNeighbor;
    AllNeighbor.reserve(1<<n);
    AllNeighbor[0] = {0};

    bool lastOne =0;
    FindAllnx1(Allnx1, 0, n, lastOne, 0, AllNeighborConstraint, AllNeighbor);

    

    ll maxMask = (1<<n);
    
    vector<vector<ll>> dp(n, vector<ll>(maxMask, 0));

    // setting the base case
    for(auto &mask : Allnx1)
    {
        if((mask & obstical[0]) == 0)
        {
            dp[0][mask] = 1;
        }
    }

    // for(auto &mask : Allnx1)
    // {
    //     cout<<"dp[0]["<<mask<<"]: "<<dp[0][mask]<<"\n";
    // }

    // for(auto &mask : Allnx1)
    // {
    //     cout<<"mask: "<<mask<<" neighbour: ";
    //     for(auto &neighbour : AllNeighbor[mask])
    //     {
    //         cout<<neighbour<<" ";
    //     }
    //     cout<<"\n";
    // }

    for(int i=1; i<n; i++)
    {
        for(auto &crtMask : Allnx1)
        {
            if(crtMask & obstical[i])
            {
                //cout<<"meet obstical\n";
                continue;
            }

            //cout<< crtMask<<"'s neighbour is:  "<<neighbourConstraint<<"\n";

            for(auto &neighborMask : AllNeighbor[crtMask])
            {
                //cout<<prevMask<< " & "<<neighbourConstraint<<": "<<(prevMask & neighbourConstraint)<<"\n";
                dp[i][crtMask] += dp[i - 1][neighborMask];
                dp[i][crtMask] %= MOD;
            }

            //cout<<"dp["<<i<<"]["<<crtMask<<"]: "<<dp[i][crtMask]<<"\n";
        }
    }


    ll result = 0;

    for(auto &mask : Allnx1)
    {
        result += dp[n-1][mask];
        result %= MOD;
    }

    cout<<result<<"\n";
    return 0;
}