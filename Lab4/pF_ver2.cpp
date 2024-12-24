#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

using ll = long long;

struct Custom
{
    bool operator()(const pair<int, int> &a, const pair<int, int> &b) const
    {
        if(a.first == b.first)
        {
            return false;
        }

        return a.first > b.first;
    }
};

void UpdateLvl(vector<ll> &segmentTree,int rootStart, int upperRange, int lowerRange, ll reward)
{
    
    int newLvl = upperRange + rootStart + 1;

    //cout<<"newLvl: "<<newLvl;

    ll maxReward = 0;
    int l = lowerRange + rootStart;
    int r = upperRange + rootStart;
    while(r > l)
    {
        if (l % 2 == 0)
        {
            maxReward = max(maxReward, segmentTree[l]);
            l++;
        }

        if (r % 2 == 1)
        {
            maxReward = max(maxReward, segmentTree[r]);
            r--;
        }

        l = (l-1)/2;
        r = (r-1)/2;
    }

    if(l==r)
    {
        maxReward = max(maxReward, segmentTree[l]);
    }

    //cout<<" maxReward: "<<maxReward;

    segmentTree[newLvl] = reward + maxReward;

    //cout<<" This level bastRoute: "<<segmentTree[newLvl]<<"\n";

    

    newLvl = (newLvl-1)/2;

    while(newLvl != 0)
    {
        segmentTree[newLvl] = max(segmentTree[newLvl], reward + maxReward);
        newLvl = (newLvl-1)/2;
    }

    segmentTree[0] = max(segmentTree[0], reward + maxReward);
}

int main()
{
    
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin>>N;

    vector<pair<int, pair<ll, int>>> lvls(N+1); //pair<diff, pair<reward, limit>>
    vector<pair<int, int>> sortLvls(N+1); //pair<diff, lvl>
    //Note: "limit" mean the lowest level that can reach to this level

    lvls[0] = {0, {0, 0}};
    sortLvls[0] = {0, 0};
    
    for(int i=1; i<=N; i++)
    {
        int l,reward, diff;
        cin>>diff>>reward>>l;
        lvls[i] = {diff, {reward, i-l}};
        
        
        sortLvls[i] = {diff, i};
        
    }

    stable_sort(sortLvls.begin(), sortLvls.end(), Custom());

    // cout<<"sortLvls\n";
    // for(int i=0; i<=N; i++)
    // {
        
    //     cout<<sortLvls[i].first<<" "<<sortLvls[i].second<<"\n";
    // }
    // cout<<"------\n";

    vector<ll> segmentTree(4*(N+1), 0); //segment tree to store the best route

    int rootStart = 1;
    while(rootStart < N+1)
    {
        rootStart *= 2;
    }
    rootStart--;


    

    for(int i=N-1; i>=0; i--)
    {
        
        int upperRange = sortLvls[i].second-1;
        int lowerRange = lvls[sortLvls[i].second].second.second;
        //cout<<"upperRange: "<<upperRange<<" lowerRange: "<<lowerRange<<"\n";

       UpdateLvl(segmentTree, rootStart, upperRange, lowerRange, lvls[sortLvls[i].second].second.first);
    }

    cout<<segmentTree[0]<<"\n";
    return 0;
}