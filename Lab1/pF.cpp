#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>

using namespace std;



bool decreasing(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b)
{
    return a.second.second > b.second.second;
}

bool customSort(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b, long long x)
{
    long long aRes = a.second.second + a.second.first * x;
    long long bRes = b.second.second + b.second.first * x;
    if(aRes == bRes)
    {
        return a.second.first < b.second.first;
    }
    return aRes < bRes;
}

int main()
{
    int nLine, mX;
    cin >> nLine >> mX;
    vector<pair<int, pair<int, int>>> line(nLine);

    for(int i = 0; i < nLine; i++)
    {
        cin >> line[i].second.first >> line[i].second.second >> line[i].first;
    }

    sort(line.begin(), line.end(), decreasing);
    

    for(int i=0; i<mX; i++)
    {
        vector<pair<int, pair<int, int>>> copyLine = line;
        long long x;
        cin>>x;

        stable_sort(copyLine.begin(), copyLine.end(), [x](pair<int, pair<int, int>> a, pair<int, pair<int, int>> b)
        {
            return customSort(a, b, x);
        });
        long long result = 0;
        for(int j=0; j<nLine; j++)
        {
            result += copyLine[j].first * (j+1);
        }
        //cout<<"Ans: ";
        cout<<result<<endl;

    }
}