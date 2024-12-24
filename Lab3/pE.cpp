#include<iostream>
#include<queue>
#include<vector>
#include<climits>
#include<cmath>

typedef  long long   ll;

using namespace std;

class Point
{
    public:

    int loca;
    vector<vector<ll>> allRoute;
    int k;
    bool isVisited;

    vector<pair<int, ll>> adj;
    
    Point()
    {   
        isVisited = false;
    }

    

    
};

struct ComparePoint
{
    bool operator()(const Point *a, const Point *b) const
    {
        
        return a->allRoute[a->k][0] > b->allRoute[b->k][0];
    }
};
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;

    

    vector<vector<ll>> routeType(k+1);
    vector<vector<ll>> routeType1(k + 1);

    routeType[0] = {LLONG_MAX/100};
    routeType1[0] = {0};

    for(int i=1; i<=k; i++)
    {
        routeType[i] = vector<ll>(k, LLONG_MAX/100);
        routeType1[i] = vector<ll>(k, 0);
    }

    vector<ll> couponValue(k);
    for(int i=0; i<k; i++)
    {
        cin >> couponValue[i];
    }

    vector<Point> points(n);
    priority_queue<Point *,vector<Point*>, ComparePoint> pq;

    points[0].loca = 0;
    points[0].allRoute = routeType1;
    points[0].k = k;
    

    for(int i=1; i<n; i++)
    {
        points[i].loca = i;
        points[i].allRoute = routeType;
        points[i].k = k;
    }

    

    for(int i=0; i<m;i++)
    {
        int u, v;
        ll w;
        cin >> u >> v >> w;

        u-=1;
        v-=1;

        points[u].adj.push_back({v, w});
        points[v].adj.push_back({u, w});

    }

    ll result=-1;


    pq.push(&points[0]);
    
    
    while(!pq.empty())
    {
        //cout<<"now crt is P"<<pq.top()->loca<<endl;

        Point* crt = pq.top();
        pq.pop();
        
        if (crt->isVisited)
        {
            continue;
        }
        points[crt->loca].isVisited = true;

        if (crt->loca == n - 1)
        {
            for(int i=0; i<=k; i++)
            {
                result = LLONG_MAX;
                for(int j=0; j<crt->allRoute[i].size(); j++)
                {
                    result = min(result, crt->allRoute[i][j]);
                }
            }
            break;
        }

        for (int neib = 0; neib < crt->adj.size(); neib++) // all neighbors
        {
            Point *neibPoint = &points[crt->adj[neib].first];
            if(neibPoint->isVisited)
            {
                //cout<<"P"<<neibPoint->loca<<" is visited"<<endl;
                continue;
            }
            bool isNeedPush = false;
            
            if (k == 0)
            {
                if ( neibPoint->allRoute[0][0] > crt->allRoute[0][0] + crt->adj[neib].second)
                {
                    isNeedPush = true;
                    neibPoint->allRoute[0][0] = crt->allRoute[0][0] + crt->adj[neib].second;
                }
            }
            else if (k == 1)
            {
                // no coupon -> no coupon used
                if ( neibPoint->allRoute[0][0] >= crt->allRoute[0][0] + crt->adj[neib].second)
                {
                    //isNeedPush = true;
                    neibPoint->allRoute[0][0] = crt->allRoute[0][0] + crt->adj[neib].second;
                }
                double temp = crt->adj[neib].second / couponValue[0];
                ll t1 = temp;
                // no coupon -> 1 coupon used
                if (neibPoint->allRoute[1][0] >= crt->allRoute[0][0] + t1)
                {
                    isNeedPush = true;
                    neibPoint->allRoute[1][0] = crt->allRoute[0][0] + t1;
                }

                // 1 coupon -> 1 coupon used
                if ( neibPoint->allRoute[1][0] >= crt->allRoute[1][0] + crt->adj[neib].second)
                {
                    isNeedPush = true;
                    neibPoint->allRoute[1][0] = crt->allRoute[1][0] + crt->adj[neib].second;
                }
            }
            else if (k == 2)
            {
                // no coupon -> no coupon used
                if (neibPoint->allRoute[0][0] > crt->allRoute[0][0] + crt->adj[neib].second)
                {
                    isNeedPush = true;
                    neibPoint->allRoute[0][0] = crt->allRoute[0][0] + crt->adj[neib].second;
                }

                // no coupon -> 1 coupon used
                for (int i = 0; i < k; i++)
                {
                    if (neibPoint->allRoute[1][i] > crt->allRoute[0][0] + crt->adj[neib].second / couponValue[i])
                    {
                        isNeedPush = true;
                        neibPoint->allRoute[1][i] = crt->allRoute[0][0] + crt->adj[neib].second / couponValue[i];
                    }
                }

                // 1 coupon -> 1 coupon used
                for (int i = 0; i < k; i++)
                {
                    if ( neibPoint->allRoute[1][i] > crt->allRoute[1][i] + crt->adj[neib].second)
                    {
                        isNeedPush = true;
                        neibPoint->allRoute[1][i] = crt->allRoute[1][i] + crt->adj[neib].second;
                    }

                    // 1 coupon -> 2 coupon used
                    int p1 = (i + 1) % k;
                    if ( neibPoint->allRoute[2][0] > crt->allRoute[1][i] + crt->adj[neib].second / couponValue[p1])
                    {
                        isNeedPush = true;
                        neibPoint->allRoute[2][0] = crt->allRoute[1][i] + crt->adj[neib].second / couponValue[p1];
                    }
                }
            }
            else if (k == 3)
            {
                // no coupon -> no coupon used
                if ( neibPoint->allRoute[0][0] > crt->allRoute[0][0] + crt->adj[neib].second)
                {
                    isNeedPush = true;
                    neibPoint->allRoute[0][0] = crt->allRoute[0][0] + crt->adj[neib].second;
                }

                // no coupon -> 1 coupon used
                for (int i = 0; i < k; i++)
                {
                    if (neibPoint->allRoute[1][i] > crt->allRoute[0][0] + crt->adj[neib].second / couponValue[i])
                    {
                        isNeedPush = true;
                        neibPoint->allRoute[1][i] = crt->allRoute[0][0] + crt->adj[neib].second / couponValue[i];
                    }
                }

                // 1 coupon -> 1 coupon used
                for (int i = 0; i < k; i++)
                {
                    if ( neibPoint->allRoute[1][i] > crt->allRoute[1][i] + crt->adj[neib].second)
                    {
                        isNeedPush = true;
                        neibPoint->allRoute[1][i] = crt->allRoute[1][i] + crt->adj[neib].second;
                    }

                    // 1 coupon -> 2 coupon used
                    int p1 = (i + 1) % k;
                    int p2 = (i + 2) % k;
                    if ( neibPoint->allRoute[2][p1] > crt->allRoute[1][i] + crt->adj[neib].second / couponValue[p2])
                    {
                        isNeedPush = true;
                        neibPoint->allRoute[2][p1] = crt->allRoute[1][i] + crt->adj[neib].second / couponValue[p2];
                    }
                    if ( neibPoint->allRoute[2][p2] > crt->allRoute[1][i] + crt->adj[neib].second / couponValue[p1])
                    {
                        isNeedPush = true;
                        neibPoint->allRoute[2][p2] = crt->allRoute[1][i] + crt->adj[neib].second / couponValue[p1];
                    }
                }

                // 2 coupon -> 2 coupon used
                for (int i = 0; i < k; i++)
                {
                    if (neibPoint->allRoute[2][i] > crt->allRoute[2][i] + crt->adj[neib].second)
                    {
                        isNeedPush = true;
                        neibPoint->allRoute[2][i] = crt->allRoute[2][i] + crt->adj[neib].second;
                    }

                    // 2 coupon -> 3 coupon used
                    if (neibPoint->allRoute[3][0] > crt->allRoute[2][i] + crt->adj[neib].second / couponValue[i])
                    {
                        isNeedPush = true;
                        neibPoint->allRoute[3][0] = crt->allRoute[2][i] + crt->adj[neib].second / couponValue[i];
                    }
                }
            }

            // if (isNeedPush)
            // {
                //cout<<"push P"<<neibPoint->loca<<endl;
                pq.push(neibPoint);
            // }
        }

        
    }

    
    cout << result << endl;
    
   

    return 0;
}