#include <iostream>
#include <vector>

using namespace std;

void Rule1(vector<pair<int, pair<int, int>>> &v, int loca);

void Rule3(vector<pair<int, pair<int, int>>> &v, int loca)
{
    if(v[loca].second.second >= v[loca - 1].second.second)  //v[loca].second == v[loca-1].second is Rule4
    {
        return ;
    }
    else    //v[loca].second < v[loca].second
    {
        swap(v[loca], v[loca-1]);

        if(loca == 1)
        {
            return;
        }
        else
        {
            Rule1(v, --loca);
            return ;
        }
    }
}

void Rule2(vector<pair<int, pair<int, int>>> &v, int loca)
{
    if(v[loca].second.second%2 == 0 && v[loca-1].second.second%2 == 1)
    {
        return ;
    }
    else if (v[loca].second.second % 2 == 1 && v[loca - 1].second.second % 2 == 0)
    {
        swap(v[loca], v[loca - 1]);
        
        if(loca == 1)
        {
            return;
        }
        else
        {
            Rule1(v, --loca);
            return ;
        }
    }
    else          //Both odd or both even
    {
        Rule3(v, loca);
        return ;
    }
}

void Rule1(vector<pair<int, pair<int, int>>> &v, int loca)
{
    if (v[loca].second.first > v[loca - 1].second.first)
    {
        swap(v[loca], v[loca - 1]);

        if (loca == 1)
        {
            return;
        }
        else
        {
            Rule1(v, --loca);
            return;
        }
    }
    else if (v[loca].second.first == v[loca - 1].second.first)
    {
        Rule2(v, loca);
        return;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<pair<int, pair<int, int>>> v;      //index, pair(x, y)
    for(int i=0;i<n;i++)
    {
        int x, y;
        cin >> x >> y;
        

        v.push_back({i+1, {x, y}});
        int loca = v.size() - 1;

        if(loca != 0)
        {
            Rule1(v, loca);   
        }
    }
    
    for(int i=0;i<n;i++)
    {
        cout<<v[i].first<<" ";
    }

    return 0;
}