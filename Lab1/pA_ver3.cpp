#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

bool isNeedRule2=false;


bool Rule1Sort(const pair<int, pair<int, int>> &a, const pair<int, pair<int, int>> &b)
{
    if(a.second.first > b.second.first)
    {
        return true;
    }
    else if(a.second.first == b.second.first)
    {
        isNeedRule2=true;
        return false;
    }
    else
    {
        return false;
    }
}

bool Rule23Sort(const pair<int, pair<int, int>> &a, const pair<int, pair<int, int>> &b)
{
    
    if(a.second.second%2 == 1 && b.second.second%2 == 0)
    {
        return true;
    }
    else if(a.second.second%2 == b.second.second%2 )    
    {
        if(a.second.second > b.second.second)
        {
            return false;
        }
        else if(a.second.second == b.second.second)
        {
            if(a.first < b.first)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}

void R23Sort(vector<pair<int, pair<int, int>>> &v)
{
    int currentSet=v[0].second.first;
    int begin=0;
    for(int i=0;i<v.size();i++)
    {
        if(v[i].second.first!=currentSet)
        {
            //Insertion sort
            sort(v.begin()+begin,v.begin()+i,Rule23Sort);
            currentSet=v[i].second.first;
            begin=i;
        }
    }
        
    sort(v.begin()+begin,v.end(),Rule23Sort);
   
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<pair<int, pair<int, int>>> v;
    for(int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        v.push_back({i+1, {x, y}});
    }

    stable_sort(v.begin(), v.end(), Rule1Sort);

    if(isNeedRule2)
    {
       R23Sort(v);
    }

    for(int i = 0; i < n; i++)
    {
        cout << v[i].first << " ";
    }
    cout << endl;
    return 0;
}