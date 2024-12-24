#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>

using namespace std;

bool customSort(pair<int, long long> a, pair<int, long long> b)
{
    return a.second < b.second;
}


//path to prefixSum[x] to prefixSum[x+1] is illegal, must be x+2 or more

pair<long long, pair<int, int>> FindShortestPath(vector<pair<int, long long>> &prefixSum, int l, int r)
{
    if(r-l <= 1) //1 or 2 elements
    {
        return {0, {0, 0}};
    }
    else if (r - l == 2) // 3 elements, only 1 legal path
    {
        long long x2 = pow(l-r, 2);
        long long y2;
        if (abs(prefixSum[l].second - prefixSum[r].second) > pow(10,8))
        {
            y2 = pow(10, 16);
        }
        else
        {
            y2 = pow(prefixSum[l].second - prefixSum[r].second, 2);
        }
            

        return {x2 + y2, {l, r}};
    }
    else if (r - l == 3) // 4 elements, 3 legal paths
    {
        long long x2 = pow(l-r, 2);
        long long y2;
        if (abs(prefixSum[l].second - prefixSum[r].second) > pow(10,8))
        {
            y2 = pow(10, 16);
        }
        else
        {
            y2 = pow(prefixSum[l].second - prefixSum[r].second, 2);
        }

        long long x2_2 = pow(l-(r-1), 2);
        long long y2_2;
        if (abs(prefixSum[l].second - prefixSum[r-1].second) > pow(10,8))
        {
            y2_2 = pow(10, 16);
        }
        else
        {
            y2_2 = pow(prefixSum[l].second - prefixSum[r - 1].second, 2);
        }

        long long x2_3 = pow((l+1)-r, 2);
        long long y2_3;
        if (abs(prefixSum[l+1].second - prefixSum[r].second) > pow(10,8))
        {
            y2_3 = pow(10, 16);
        }
        else
        {
            y2_3 = pow(prefixSum[l + 1].second - prefixSum[r].second, 2);
        }

        long long path1 = x2 + y2;
        long long path2 = x2_2 + y2_2;
        long long path3 = x2_3 + y2_3;

        if(path1 <= path2 && path1 <= path3)
        {
            return {path1, {l, r}};
        }
        else if(path2 <= path1 && path2 <= path3)
        {
            return {path2, {l, r-1}};
        }
        else if(path3 <= path1 && path3 <= path2)
        {
            return {path3, {l+1, r}};
        }
    }

    //from now on, there are 5 or more elements, which it can be return a viable shortest path from left or right side

    int midP = (l + r) / 2; //consider in left side
    pair<long long, pair<int, int>> sPathL = FindShortestPath(prefixSum, l, midP);
    pair<long long, pair<int, int>> sPathR = FindShortestPath(prefixSum, midP + 1, r);

    pair<long long, pair<int, int>> sPath = {(long long)pow(10,16), {0, 0}};

    if (sPathL.first!=0 && sPathR.first!=0)
    {
        if(sPathL.first <= sPathR.first)
        {
            sPath = sPathL;
        }
        else
        {
            sPath = sPathR;
        }
    }
    else if(sPathL.first!=0)
    {
        sPath = sPathL;
    }
    else if(sPathR.first!=0)
    {
        sPath = sPathR;
    }
    

    vector<pair<int, long long>> middle(r-l+1); //contain at most r-l+1 elements(aka all the elements)
    int middleSize = 0;
    long long actualPath = sqrt(sPath.first);
    if(actualPath*2 > r-l)
    {
        copy(prefixSum.begin() + l, prefixSum.begin() + r + 1, middle.begin());
        middleSize = r-l+1;
    }
    else
    {
        for (int i = l; i <= r; i++)
        {
            if (prefixSum[i].first >= (prefixSum[midP].first - actualPath - 1) && prefixSum[i].first <= (prefixSum[midP].first + actualPath + 1))
            {
                middle[middleSize] = prefixSum[i];
                middleSize++;
            }
            else if (prefixSum[i].first > (prefixSum[midP].first + actualPath + 1))
            {
                break;
            }
        }
    }

    middle.resize(middleSize);

    //and then sort by y (intcreasing order)
    sort(middle.begin(), middle.end(), customSort);

    for(int i=0;i<middle.size(); i++)
    {
        for(int j=i+1; j<middle.size() && j<=i+7; j++)
        {
            long long x2 = pow(middle[i].first - middle[j].first, 2);
            long long y2;
            long long yLength = abs(middle[i].second - middle[j].second);
            if (yLength > pow(10,8))
            {
                continue;
                y2 = pow(10, 16);
            }
            else
            {
                y2 = pow(yLength, 2);
            }

            if(x2 + y2 < sPath.first && x2 > 1)
            {
                
                sPath = {x2 + y2, {middle[i].first, middle[j].first}};
            }
        }
    }

    return sPath;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<pair<int, long long>> prefixSum(n+1); //(x, y)
    prefixSum[0] = {0, 0};

    for(int i=1;i<=n;i++)
    {
        long long x;
        cin >> x;
        prefixSum[i] = {i, prefixSum[i-1].second + x};
    }

    pair<long long, pair<int, int>> shortestPath = FindShortestPath(prefixSum, 0, n); //(length, (start.x, end.x))

    int small = min(shortestPath.second.first, shortestPath.second.second);
    int big = max(shortestPath.second.first, shortestPath.second.second);
    //cout<<shortestPath.first<<endl;
    cout<<small+1<<" "<<big<<endl;

    return 0;
}