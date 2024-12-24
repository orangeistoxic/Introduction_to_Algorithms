#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
typedef long long ll;

using namespace std;

#pragma warning(disable: 4996)

const long long INF = 5 * pow(10, 16);
const long long MAX = 2 * pow(10, 8);

bool CustomSortY(pair<int, ll> a, pair<int, ll> b)
{
    
    return a.second < b.second;
}

pair<ll, pair<int, int>>  FindShortestPath(vector<pair<int, ll>> cX, vector<pair<int, ll>> cY)
{
    if(cX.size() == 1) //1 element
    {
        return {INF, {0, 0}};
    }
    else if(cX.size() == 2) //2 elements
    {
        ll x2 = pow(cX[0].first - cX[1].first, 2);
        ll y = abs(cX[0].second - cX[1].second);
        if(x2 > 1 && y <= MAX) //in case of illegal path and overflow from y
        {
            ll y2 = pow(y, 2);
            return {x2 + y2, {cX[0].first, cX[1].first}};
        }
        else
        {
            return {INF, {0, 0}};
        }
    }
    
    // int midP = (cY.size() - 1) / 2; //this value is nor x or y
    // ll midPYValue = cY[midP].second;
    // vector<pair<int, ll>> lcY(cY.begin(), cY.begin() + midP + 1);
    // vector<pair<int, ll>> rcY(cY.begin() + midP + 1, cY.end());
    // vector<pair<int, ll>> lcX(lcY.size()), rcX(rcY.size());
    // int l = 0, r = 0;
    // for(int i=0;i<cX.size(); i++)
    // {
    //     if(cX[i].second < midPYValue)
    //     {
    //         lcX[l] = cX[i];
    //         l++;
    //     }
    //     else if(cX[i].second == midPYValue)
    //     {
    //         if(l < lcX.size())
    //         {
    //             lcX[l] = cX[i];
    //             l++;
    //         }
    //         else
    //         {
    //             rcX[r] = cX[i];
    //             r++;
    //         }
    //     }
    //     else
    //     {
    //         rcX[r] = cX[i];
    //         r++;
    //     }
    // }
    

    int midP = (cX.size() - 1) / 2; //this value is nor x or y
    ll midPXValue = cX[midP].first;
    vector<pair<int, ll>> lcX(cX.begin(), cX.begin() + midP + 1);
    vector<pair<int, ll>> rcX(cX.begin() + midP + 1, cX.end());
    vector<pair<int, ll>> lcY(lcX.size()), rcY(rcX.size());
    int l = 0, r = 0;
    for(int i=0;i<cY.size(); i++)
    {
        if(cY[i].first <= midPXValue)
        {
            lcY[l] = cY[i];
            l++;
        }
        else
        {
            rcY[r] = cY[i];
            r++;
        }
    }

    pair<ll, pair<int, int>> sPathL = FindShortestPath(lcX, lcY);
    pair<ll, pair<int, int>> sPathR = FindShortestPath(rcX, rcY);

    pair<ll, pair<int, int>> sPath = {INF, {0, 0}};
    if (sPathL.first <= sPathR.first)
    {
        sPath = sPathL;
    }
    else
    {
        sPath = sPathR;
    }

    //contain at most r-l+1 elements(aka all the elements in this recursion)
    // vector<pair<int, ll>> middle(cX.size());
    // int middleSize = 0;
    // ll actualPath = sqrt(sPath.first);
    // ll lowerBound = cY[midP].second - actualPath - 1;
    // ll upperBound = cY[midP].second + actualPath + 1;

    // for(int i=0;i<cX.size(); i++)
    // {
    //     if(cX[i].second >= lowerBound && cX[i].second <= upperBound)
    //     {
    //         middle[middleSize] = cX[i];
    //         middleSize++;
    //     }
    // }

    // middle.resize(middleSize);

    // for(int i=0;i<middle.size(); i++)
    // {
    //     for(int j=i+1; j<middle.size() && j<=i+7; j++)
    //     {
    //         ll x2 = pow(middle[i].first - middle[j].first,2);
    //         ll y = abs(middle[i].second - middle[j].second);
    //         if(x2 > 1 && y <= MAX)
    //         {
    //             ll y2 = pow(y, 2);
    //             if(x2 + y2 < sPath.first)
    //             {
    //                 sPath = {x2 + y2, {middle[i].first, middle[j].first}};
    //             }
    //         }
    //     }
    // }

    vector<pair<int, ll>> middle(cY.size());
    int middleSize = 0;
    ll actualPath = sqrt(sPath.first);
    ll lowerBound = cX[midP].first - actualPath - 1;
    ll upperBound = cX[midP].first + actualPath + 1;

    for(int i=0;i<cY.size();i++)
    {
        if(cY[i].first >= lowerBound && cY[i].first <= upperBound)
        {
            middle[middleSize] = cY[i];
            middleSize++;
        }
    }

    middle.resize(middleSize);

    for(int i=0;i<middle.size(); i++)
    {
        for(int j=i+1; j<middle.size() && j<=i+2; j++)
        {
            ll x2 = pow(middle[i].first - middle[j].first,2);
            ll y = abs(middle[i].second - middle[j].second);
            if(x2 > 1 && y <= MAX)
            {
                ll y2 = pow(y, 2);
                if(x2 + y2 < sPath.first)
                {
                    sPath = {x2 + y2, {middle[i].first, middle[j].first}};
                }
            }
        }
    }

    return sPath;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(false);

    int n;
    cin >> n;
    vector<pair<int, ll>> coordinateX(n + 1); //(x, y)
    coordinateX[0] = {0, 0};
    for(int i=1;i<=n;i++)
    {
        ll x;
        cin >> x;
        coordinateX[i] = {i, coordinateX[i - 1].second + x};
        
    }

    vector<pair<int, ll>> coordinateY = coordinateX;
    sort(coordinateY.begin(), coordinateY.end(), CustomSortY);

    pair<ll, pair<int, int>> shortestPath = FindShortestPath(coordinateX,coordinateY); //(length, (start.x, end.x))

    int small = min(shortestPath.second.first, shortestPath.second.second);
    int big = max(shortestPath.second.first, shortestPath.second.second);
    // cout<<shortestPath.first<<endl;
    cout << small + 1 << " " << big << endl;

    return 0;
}