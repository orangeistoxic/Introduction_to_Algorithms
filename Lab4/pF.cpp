#include<iostream>
#include<vector>

using namespace std;

using ll = long long;

class Lvl
{
    public:
        int diff, limit;
        ll reward, bestRoute;

        Lvl()
        {
            diff = 0;
            reward = 0;
            limit = 0;
            bestRoute = 0;
        }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin>>N;
    vector<Lvl> lvls(N);

    for(int i=0; i<N; i++)
    {
        cin>>lvls[i].diff>>lvls[i].reward>>lvls[i].limit;
        lvls[i].bestRoute = lvls[i].reward;
    }

    ll maxReward = lvls[N-1].bestRoute;
    for(int i=N-1;i>=0; i--)
    {
        maxReward = max(maxReward, lvls[i].bestRoute);
        for(int j=i-1;j>=i-lvls[i].limit; j--)
        {
            if(lvls[i].diff > lvls[j].diff)
            {
                lvls[j].bestRoute = max(lvls[j].bestRoute, lvls[j].reward + lvls[i].bestRoute);
                
            }
            else if (lvls[i].diff < lvls[j].diff && lvls[i].bestRoute < lvls[j].bestRoute)
            {
                break;
            }
        }
        
    }

    cout<<maxReward<<"\n";

    return 0;
}