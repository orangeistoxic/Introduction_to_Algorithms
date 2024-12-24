#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>

using namespace std;



bool custom(pair<double, pair<double, double>> a, pair<double, pair<double, double>> b)
{
    return a.first > b.first;
}




int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    
    vector<pair<int[3], int[3]>> rounds(n);
    vector<pair<double, pair<double, double>>> possi;
    possi.reserve(100);
    possi.push_back({1, {0, 0}});

    for(int i=0;i<n;i++)
    {
        cin >> rounds[i].first[0] >> rounds[i].second[0];
        if(rounds[i].first[0] < rounds[i].second[0])
        {
            swap(rounds[i].first[0], rounds[i].second[0]);
        }
        cin >> rounds[i].first[1] >> rounds[i].second[1];
        if(rounds[i].first[1] < rounds[i].second[1])
        {
            swap(rounds[i].first[1], rounds[i].second[1]);
        }
        cin >> rounds[i].first[2] >> rounds[i].second[2];
        if(rounds[i].first[2] < rounds[i].second[2])
        {
            swap(rounds[i].first[2], rounds[i].second[2]);
        }
    }

    for(int i=0;i<n;i++)
    {
        int lastSize = possi.size();
        double newX, newY, newR;
        for(int j=0;j<lastSize;j++)
        {
            newX = (double)rounds[i].first[0] + (double)possi[j].second.first;
            newY = (double)rounds[i].second[0] + (double)possi[j].second.second;
            newR = newX/newY;
            possi.push_back({newR, {newX, newY}});

            newX = (double)rounds[i].first[1] + (double)possi[j].second.first;
            newY = (double)rounds[i].second[1] + (double)possi[j].second.second;
            newR = newX/newY;
            possi.push_back({newR, {newX, newY}});

            newX = (double)rounds[i].first[2] + (double)possi[j].second.first;
            newY = (double)rounds[i].second[2] + (double)possi[j].second.second;
            newR = newX/newY;
            possi[j] = {newR, {newX, newY}};
        }

        sort(possi.begin(), possi.end(), custom);

        if(possi.size() > 30)
        {
            possi.resize(30);
        }
    }

    cout << possi[0].first << endl;
    
    

    

    return 0;
}