#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
//v[i+1]=a, v[i]=b
//true is swap, false is not swap
bool Rule(const pair<int, pair<int, int>> &a, const pair<int, pair<int, int>> &b)
{

    //Rule1
    if(a.second.first > b.second.first)
    {
        return true;
    }
    else if(a.second.first == b.second.first) //into Rule2
    {
        if(a.second.second%2 == 0 && b.second.second%2 == 1)
        {
            return false;
        }
        else if(a.second.second%2 == 1 && b.second.second%2 == 0)
        {
            return true;
        }
        else //into Rule3
        {
            if(a.second.second >= b.second.second) // Rule4
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }
    else
    {
        return false;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<pair<int, pair<int, int>>> v;

    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        v.push_back({i, {a, b}});
        sort(v.begin(), v.end(), Rule);
    }
    
    for (int i = 0; i < n; i++)
    {
        cout << v[i].first + 1 << " ";
    }
    cout <<endl;
    return 0;

    
}