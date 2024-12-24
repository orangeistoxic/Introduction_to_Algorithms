#include<iostream>
#include <vector>
#include <stack>

using namespace std;

class Point
{
public:
    int height;
    int start;
    int finish;
    bool isV;

    Point()
    {
        height = -1;
        start = -1;
        finish = -1;
        isV = false;
    }
};

void DFS(vector<vector<Point>> &grid, vector<pair<int, int>> &st, int i, int j, int &cnt, int &n, int &m)
{
    grid[i][j].start = cnt;
    cnt++;

    if(i-1 >= 0 && grid[i-1][j].height <= grid[i][j].height)
    {
        if(grid[i-1][j].start == -1)
        {
            DFS(grid, st, i-1, j, cnt, n, m);
        }
    }
    if(i+1 < n && grid[i+1][j].height <= grid[i][j].height)
    {
        if(grid[i+1][j].start == -1)
        {
            DFS(grid, st, i+1, j, cnt, n, m);
        }
    }
    if(j-1 >= 0 && grid[i][j-1].height <= grid[i][j].height)
    {
        if(grid[i][j-1].start == -1)
        {
            DFS(grid, st, i, j-1, cnt, n, m);
        }
    }
    if(j+1 < m && grid[i][j+1].height <= grid[i][j].height)
    {
        if(grid[i][j+1].start == -1)
        {
            DFS(grid, st, i, j+1, cnt, n, m);
        }
    }

    grid[i][j].finish = cnt;
    cnt++;
    
    st.push_back({i, j});
}

void DFS2(vector<vector<Point>> &grid, int i, int j, int &n, int &m)
{
    grid[i][j].isV = true;

    if(i-1 >= 0 && grid[i-1][j].height <= grid[i][j].height)
    {
        if(grid[i-1][j].isV == false)
        {
            DFS2(grid, i-1, j, n, m);
        }
    }
    if(i+1 < n && grid[i+1][j].height <= grid[i][j].height)
    {
        if(grid[i+1][j].isV == false)
        {
            DFS2(grid, i+1, j, n, m);
        }
    }
    if(j-1 >= 0 && grid[i][j-1].height <= grid[i][j].height)
    {
        if(grid[i][j-1].isV == false)
        {
            DFS2(grid, i, j-1, n, m);
        }
    }
    if(j+1 < m && grid[i][j+1].height <= grid[i][j].height)
    {
        if(grid[i][j+1].isV == false)
        {
            DFS2(grid, i, j+1, n, m);
        }
    }


}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    int tot= n*m;

    vector<vector<Point>> grid(n, vector<Point>(m));
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            cin >> grid[i][j].height;
        }
    }

    int cnt = 0;
    //do topological sort first, then do DFS until all nodes are visited
    vector<pair<int, int>> st;
    st.reserve(tot);
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            if(grid[i][j].start == -1)
            {
                DFS(grid, st, i, j, cnt, n, m);
            }
        }
    }

    
    // for(int i=0; i<st.size(); i++)
    // {
    //     cout <<"location: " << st[i].first << " " << st[i].second << " start: " << grid[st[i].first][st[i].second].start << " finish: " << grid[st[i].first][st[i].second].finish << endl;
    // }

    int DFSTree = 0;
    for(int i=st.size()-1; i>=0; i--)
    {
        if(grid[st[i].first][st[i].second].isV == false)
        {
            DFSTree++;
            DFS2(grid, st[i].first, st[i].second, n, m);
        }
    }

    cout << DFSTree << endl;
    
    return 0;
}