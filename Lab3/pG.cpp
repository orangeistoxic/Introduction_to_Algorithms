#include<iostream>
#include<vector>
#include<climits>
#include<queue>

using namespace std;

using ll = long long;
using pli = pair<ll, int>;
using pil = pair<int, ll>;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N, M;
    cin>> N >> M;

    vector<vector<pil>> G(N, vector<pil>()); //pair<neighbor, weight>
    for(int i=0; i<M; ++i)
    {
        int u, v;
        ll w;
        cin>>u>>v>>w;

        u--; v--;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }

    vector<pli> MST(N, pli(LLONG_MAX, -1)); // pair<weight, parent>
    vector<bool> isVisited(N, false);

    int visitedCount = 0;
    ll totWeight = 0;

    priority_queue<pair<pli, int>, vector<pair<pli, int>>, greater<>> pq;
    MST[0] = pli(0, 0);
    pq.push({MST[0], 0});

    while(!pq.empty())
    {
        auto [crtInfo, crtNode] = pq.top();
        pq.pop();
        if(isVisited[crtNode])
        {
            continue;
        }

        isVisited[crtNode] = true;
        visitedCount++;
        totWeight += crtInfo.first;

        for(int i=0;i<G[crtNode].size(); ++i)
        {
            auto [NB, NBW] = G[crtNode][i];

            if(isVisited[NB])
            {
                continue;
            }

            if(MST[NB].first > NBW)
            {
                MST[NB] = pli(NBW, crtNode);
                pq.push({MST[NB], NB});
            }
        }
    }

    if(visitedCount != N)
    {
        cout<< -1 << endl;
    }
    else
    {
        cout<< totWeight << endl;
    }
    return 0;
}