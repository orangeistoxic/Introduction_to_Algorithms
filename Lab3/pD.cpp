// Make Maximun Spanning Tree, and then use common ancestor to find the path
#include<iostream>
#include<vector>
#include<queue>
#include<climits>

using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pil = pair<int, ll>;
using pli = pair<ll, int>;



int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N, M;
    cin>>N>>M;

    vector<vector<pil>> Graph(N, vector<pil>()); //contain its neighbor and weight

    for(int i=0; i<M; i++)
    {
        int u, v;
        ll w;
        cin>>u>>v>>w;
        u--;
        v--;
        Graph[u].emplace_back(v, w);
        Graph[v].emplace_back(u, w);
    }

    vector<pli> MaxST(N, pli(-1, -1)); // pair<weight, parent>
    vector<int> depth(N, 0);
    vector<bool> isVisited(N, false);
    priority_queue<pair<pli, int>> pq;
    MaxST[0] = pli(0, 0);
    pq.push({MaxST[0], 0});

    while (!pq.empty())
    {
        auto [crtInfo, crtNode] = pq.top();
        pq.pop();
        isVisited[crtNode] = true;

        for (int i = 0; i < Graph[crtNode].size(); ++i)
        {
            auto [NB, NBW] = Graph[crtNode][i];
            if (isVisited[NB])
            {
                continue;
            }

            if (Graph[crtNode][i].second > MaxST[NB].first)
            {
                MaxST[NB] = pli(NBW, crtNode);
                depth[NB] = depth[crtNode] + 1;
                pq.push({MaxST[NB], NB});
            }
        }
    }

        // MaxST is done

        // Start LCA
        int Q;
        cin>>Q;
        while(Q--)
        {
            int pA, pB;
            cin>>pA>>pB;

            pA--;
            pB--;
            ll minWeightLimit = LLONG_MAX;

            if(depth[pA] < depth[pB])
            {
                int diff = depth[pB] - depth[pA];
                while(diff--)
                {
                    minWeightLimit = min(minWeightLimit, MaxST[pB].first);
                    pB = MaxST[pB].second; //become parent
                }
            }
            else if(depth[pA] > depth[pB])
            {
                int diff = depth[pA] - depth[pB];
                while(diff--)
                {
                    minWeightLimit = min(minWeightLimit, MaxST[pA].first);
                    pA = MaxST[pA].second; //become parent
                }
            }

            //cout<<"Check: "<< depth[pA] << " " << depth[pB] << endl;

            while(pA != pB)
            {
                minWeightLimit = min(minWeightLimit, MaxST[pA].first);
                minWeightLimit = min(minWeightLimit, MaxST[pB].first);
                pA = MaxST[pA].second;
                pB = MaxST[pB].second;
            }

            cout<<minWeightLimit<<endl;


        }

        
    


    return 0;
}