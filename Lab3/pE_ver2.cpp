#include<iostream>
#include<queue>
#include<vector>
#include<climits>

using ll = long long;

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m, k;
    cin>>n>>m>>k;

    vector<ll> coupon(k);
    for(int i=0; i<k; ++i)
    {
        cin>>coupon[i];
    }

    vector<vector<pair<int, ll>>> Graph(n, vector<pair<int, ll>>());
    for(int i=0; i<m; ++i)
    {
        ll w;
        int u, v;
        cin>>u>>v>>w;
        u--;
        v--;
        Graph[u].emplace_back(v, w);
        Graph[v].emplace_back(u, w);
    }
    
    vector<vector<ll>> dist(1<<k, vector<ll>(n, LLONG_MAX));
    vector<vector<bool>> visited(1<<k, vector<bool>(n, false));
    dist[0][0] = 0;

    priority_queue<pair<ll, pair<int, int>>, vector<pair<ll, pair<int, int>>>, greater<>> pq;
    pq.push({dist[0][0], {0, 0}});// dist,{couponState, node}

    while(!pq.empty())
    {
        auto [leng, state] = pq.top();
        pq.pop();
        // remember, this is a Vertex's one cState, ONLY ONE.
        int cState = state.first;
        int node = state.second;

        if (visited[cState][node] || dist[cState][node] < leng) // why "dist[node][cState] < leng"???
        {
            continue;
        }
        visited[cState][node] = true;

        //for every current node's neighbor, check its edge
        for(int i=0; i<Graph[node].size(); ++i) 
        {
            int crtNB = Graph[node][i].first;
            ll crtW = Graph[node][i].second;
            //check current edge's couponState
            for(int a=0; a<k; ++a) 
            {
                
                //if the particular coupon is not used, then use it
                if((cState & (1<<a)) == 0)
                {
                    //cout<<"check"<<endl;
                    if(!visited[cState | (1<<a)][crtNB] && leng + crtW/coupon[a] < dist[cState | (1<<a)][crtNB])
                    {
                        dist[cState | (1<<a)][crtNB] = leng + crtW/coupon[a];
                        //cout<<"new dist is: "<<dist[cState | (1<<a)][crtNB]<<endl;
                        pq.push({dist[cState | (1<<a)][crtNB], {cState | (1<<a), crtNB}});
                    }
                }
            }

            // update the current cState. without any new coupon
            if(!visited[cState][crtNB] && leng + crtW < dist[cState][crtNB])
            {
                dist[cState][crtNB] = leng + crtW;
                pq.push({dist[cState][crtNB], {cState, crtNB}});
            }
        }
        
    }

    ll ans = LLONG_MAX;
    for(int i=0; i<(1<<k); ++i)
    {
        ans = min(ans, dist[i][n-1]);
    }

    if(ans == LLONG_MAX)
    {
        cout<<-1<<endl;
    }
    else
    {
        cout<<ans<<endl;
    }
    
    return 0;
}