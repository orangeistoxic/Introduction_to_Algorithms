#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 5*pow(10, 16);
const long long MAX = 2 * pow(10, 8);

bool CustomSortY(pair<int, long long> a, pair<int, long long> b)
{
    return a.second < b.second;
}

bool CustomSortX(pair<int, long long> a, pair<int, long long> b)
{
    return a.first < b.first;
}

pair<long long, pair<int, int>> FindShortestPath(vector<pair<int, long long>> &coordinates, int l, int r, vector<pair<int, long long>> &coordinatesX)
{
    if(r-l == 0) //1 element
    {
        return {INF, {0, 0}};
    }
    else if(r-l == 1) //2 elements
    {
        long long x2 = pow(coordinates[l].first - coordinates[r].first, 2);
        long long y = abs(coordinates[l].second - coordinates[r].second);
        if(x2 > 1 && y<=MAX) //in case of illegal path and overflow from y
        {
            long long y2 = pow(y, 2);
            return {x2 + y2, {coordinates[l].first, coordinates[r].first}};
        }
        else
        {
            return {INF, {0, 0}};
        }
    }
    // else if(r-l == 2) //3 elements, 3 possible paths
    // {
    //     long long x2_1 = pow(coordinates[l].first - coordinates[l+1].first, 2);
    //     long long y_1 = abs(coordinates[l].second - coordinates[l+1].second);
    //     pair<long long, pair<int, int>> path;
    //     if (x2_1 > 1 && y_1 <= MAX)
    //     {
    //         long long y2_1 = pow(y_1, 2);
    //         path = {x2_1 + y2_1, {coordinates[l].first, coordinates[l+1].first}};
    //     }
    //     else
    //     {
    //         path = {INF, {0, 0}};
    //     }

    //     long long x2_2 = pow(coordinates[l+1].first - coordinates[r].first, 2);
    //     long long y_2 = abs(coordinates[l+1].second - coordinates[r].second);
    //     pair<long long, pair<int, int>> path2;
    //     if (x2_2 > 1 && y_2 <= MAX)
    //     {
    //         long long y2_2 = pow(y_2, 2);
    //         path2 = {x2_2 + y2_2, {coordinates[l+1].first, coordinates[r].first}};
    //     }
    //     else
    //     {
    //         path2 = {INF, {0, 0}};
    //     }

    //     long long x2_3 = pow(coordinates[l].first - coordinates[r].first, 2);
    //     long long y_3 = abs(coordinates[l].second - coordinates[r].second);
    //     pair<long long, pair<int, int>> path3;
    //     if (x2_3 > 1 && y_3 <= MAX)
    //     {
    //         long long y2_3 = pow(y_3, 2);
    //         path3 = {x2_3 + y2_3, {coordinates[l].first, coordinates[r].first}};
    //     }
    //     else
    //     {
    //         path3 = {INF, {0, 0}};
    //     }

    //     if(path.first <= path2.first && path.first <= path3.first)
    //     {
    //         return path;
    //     }
    //     else if(path2.first <= path.first && path2.first <= path3.first)
    //     {
    //         return path2;
    //     }
    //     else
    //     {
    //         return path3;
    //     }
    // }
 
    int midP = (l + r) / 2; //this value is nor x or y
    pair<long long, pair<int, int>> sPathL = FindShortestPath(coordinates, l, midP, coordinatesX);
    pair<long long, pair<int, int>> sPathR = FindShortestPath(coordinates, midP + 1, r, coordinatesX);

    pair<long long, pair<int, int>> sPath = {(long long)pow(10, 16), {0, 0}};

    if (sPathL.first <= sPathR.first)
    {
        sPath = sPathL;
    }
    else
    {
        sPath = sPathR;
    }

    //contain at most r-l+1 elements(aka all the elements in this recursion)
    vector<pair<int, long long>> middle(r - l + 1);
    int middleSize = 0;
    long long actualPath = sqrt(sPath.first);
    long long lowerBound = coordinates[midP].second - actualPath - 1;
    long long upperBound = coordinates[midP].second + actualPath + 1;
    int lB=l, uB=r;
    for(int i=midP-1; i>=l; i--)
    {
        if(coordinates[i].second < lowerBound)
        {
            lB = i+1;
            break;
        }
    }
    for(int i=midP+1; i<=r; i++)
    {
        if(coordinates[i].second > upperBound)
        {
            uB = i-1;
            break;
        }
    }

    for(int i=lB; i<=midP; i++)
    {
        for(int j=midP+1; j<=uB && j<=midP+50; j++)
        {
            long long x2 = pow(coordinates[i].first - coordinates[j].first, 2);
            long long y = abs(coordinates[i].second - coordinates[j].second);
            if (x2 > 1 && y <= MAX)
            {
                long long y2 = pow(y, 2);
                if (x2 + y2 < sPath.first)
                {
                    sPath = {x2 + y2, {coordinates[i].first, coordinates[j].first}};
                }
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
    vector<pair<int, long long>> coordinates(n + 1); //(x, y)
    coordinates[0] = {0, 0};

    for (int i = 1; i <= n; i++)
    {
        long long x;
        cin >> x;
        coordinates[i] = {i, coordinates[i - 1].second + x};
    }
    vector<pair<int, long long>> coordinatesX = coordinates;
    sort(coordinates.begin(), coordinates.end(), CustomSortY); //sort by y (increasing order)

    pair<long long, pair<int, int>> shortestPath = FindShortestPath(coordinates, 0, n, coordinatesX); //(length, (start.x, end.x))

    int small = min(shortestPath.second.first, shortestPath.second.second);
    int big = max(shortestPath.second.first, shortestPath.second.second);
    // cout<<shortestPath.first<<endl;
    cout << small + 1 << " " << big << endl;

    return 0;
}