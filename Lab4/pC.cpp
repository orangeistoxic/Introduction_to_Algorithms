#include<iostream>
#include<vector>
#include<cmath>
#include<climits>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

class Point
{
    public:
    int loca;
    ll value;
    int start, end;
    int belongSCC;
    vector<int> adjTo, adjFrom;

    Point()
    {
        start = -1;
        end = -1;
        belongSCC = -1;
    }
};

class SCC
{
    public:
    ll value;
    int start, end;
    vector<int> adjFrom;
    ll totVal;

    SCC()
    {
        value = 0;
        start = INT_MAX;
        end = -1;
    }
};

void DFS1(vector<Point>& points, int i, int& crtTime, vector<int>& stack)
{
    points[i].start = crtTime;
    crtTime++;
    for(int j : points[i].adjTo)
    {
        if(points[j].start == -1)
        {
            DFS1(points, j, crtTime, stack);
        }
    }
    points[i].end = crtTime;
    crtTime++;
    stack.emplace_back(i);
}

void DFS2(vector<Point>& points, int &crtSCC, int i, vector<SCC>& sccs, vector<int>& stack)
{
    points[i].belongSCC = crtSCC;
    sccs[crtSCC].value += points[i].value;
    sccs[crtSCC].start = min(sccs[crtSCC].start, points[i].start);
    sccs[crtSCC].end = max(sccs[crtSCC].end, points[i].end);

    for(int j : points[i].adjFrom)
    {
        if(points[j].belongSCC == -1)
        {
            DFS2(points, crtSCC, j, sccs, stack);
        }
        else if(points[j].belongSCC != crtSCC)
        {
            sccs[crtSCC].adjFrom.emplace_back(points[j].belongSCC);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<Point> points(n);
    for(int i=0;i<n;i++)
    {
        points[i].loca = i;
        cin >> points[i].value;
    }
    for(int i=0;i<m;i++)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        points[a].adjTo.emplace_back(b);
        points[b].adjFrom.emplace_back(a);
    }

    int crtTime = 0;
    vector<int> stack;
    //do DFS first
    for(int i=0;i<n;++i)
    {
        if(points[i].start == -1)
        {
            DFS1(points, i, crtTime, stack);
        }
    }

    vector<SCC> sccs;
    vector<int> SCCstack;
    int crtSCC = 0;
    for(int i=n-1;i>=0;--i)
    {
        if(points[stack[i]].belongSCC == -1)
        {
            sccs.emplace_back();
            DFS2(points, crtSCC, stack[i],sccs, stack);
            sccs[crtSCC].totVal = sccs[crtSCC].value;
            SCCstack.emplace_back(crtSCC);
            crtSCC++;
            
        }
        
    }
    // for(SCC i: sccs)
    // {
    //     cout << i.start << " " << i.end << " " << i.value << "\n";
    // }

    for(int i= SCCstack.size()-1;i>=0;--i)
    {
        for(int j : sccs[SCCstack[i]].adjFrom)
        {
            sccs[j].totVal = max(sccs[j].totVal, sccs[j].value + sccs[SCCstack[i]].totVal);
        }
    }

    for(int i=0;i<n;++i)
    {
        cout << sccs[points[i].belongSCC].totVal << " ";
    }
    cout << "\n";

    return 0;

}