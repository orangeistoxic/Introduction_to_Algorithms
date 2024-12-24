#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<list>
#include<queue>

using namespace std;

using ll = long long;

bool BFS(vector<vector<int>> &PassToDriver, vector<int> &DriverToPass, int driver, vector<bool> &isDriverVisited, int potentialPassenger)
{
    if(isDriverVisited[driver])
    {
        return false;
    }

    isDriverVisited[driver] = true;

    if(DriverToPass[driver] == -1)
    {

        DriverToPass[driver] = potentialPassenger;
        return true;
    }
    else
    {
        int passenger = DriverToPass[driver];

        for(int i=0;i<PassToDriver[passenger].size();i++) //for this passenger, we need to find another driver for him
        {
            if(BFS(PassToDriver,DriverToPass,PassToDriver[passenger][i],isDriverVisited, passenger))
            {
                //if BFS is successful, then we need to update the assignment of driver and passenger
                DriverToPass[driver] = potentialPassenger;

                return true;
            }
        }

        return false;
    }
    
}


bool EdmondsKarp(int n, int m, vector<pair<ll,pair<ll,ll>>> &driver, vector<ll> &passenger, ll time)
{
    vector<vector<int>> PassToDriver(m);
    vector<int> DriverToPass(n,-1); //if -1, then this driver is not assigned to any passenger

    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            ll distance = abs(driver[j].first - passenger[i]);
            ll timeNeeded = driver[j].second.second + driver[j].second.first * distance;

            if(timeNeeded <= time)
            {
                PassToDriver[i].emplace_back(j);
            }
        }

        if(PassToDriver[i].size() == 0)
        {
            return false;
        }
    }

    for(int i=0;i<m ;i++) //for every passenger, we need to find a driver
    {
        vector<bool> isDriverVisited(n,false);

        bool isFound = false;

        for(int j=0;j<PassToDriver[i].size();j++)
        {
            bool isThisDriverOk = BFS(PassToDriver,DriverToPass,PassToDriver[i][j],isDriverVisited, i);

            if(isThisDriverOk)
            {
                isFound = true;
                DriverToPass[PassToDriver[i][j]] = i;
                break;
            }
        }

        if(!isFound)
        {
            return false;
        }
    }

    return true;
    
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n,m;
    cin >> n >> m;

    vector<pair<ll,pair<ll,ll>>> driver(n); //{lcoation, {multi, const}}

    ll maxTime = LLONG_MIN;
    ll minTime = 0;

    for(int i=0;i<n;i++)
    {
        cin >> driver[i].first >> driver[i].second.first >> driver[i].second.second;

        maxTime = max(maxTime, driver[i].second.second + driver[i].second.first * (abs(driver[i].first) + (1<<30)));
    }

    vector<ll> passenger(m);

    for(int i=0;i<m;i++)
    {
        cin >> passenger[i];
    }

    

    while(maxTime > minTime+1)
    {
        ll midTime = (maxTime + minTime) / 2;

        bool isPossible = EdmondsKarp(n,m,driver, passenger, midTime);

        if(isPossible)
        {
            maxTime = midTime;
        }
        else
        {
            minTime = midTime;
        }
    }

    if(EdmondsKarp(n,m,driver, passenger, minTime))
    {
        cout << minTime << endl;
    }
    else
    {
        cout << maxTime << endl;
    }

    return 0;
}