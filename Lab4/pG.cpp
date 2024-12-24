#include<iostream>
#include<vector>
#include<algorithm>
#include<assert.h>

using namespace std;

using ll = long long;

const ll MOD = 998244353;

void isPossible(vector<ll> &State, int crtX, int crtY, int &n, ll &possibleWays)
{
    //check if crtLoca is the last location
    if(crtX == n)
    {
        return;
    }    

    int newX = crtX;
    int newY = crtY+1;

    if(newY == n)
    {
        newX++;
        newY = 0;
    }

    //check if crtLoca is placible (1 is not placible, 0 is placible)
    if(State[crtX] & (1<<crtY))
    {
        //crtLoca is not placible
        isPossible(State, newX, newY, n, possibleWays);
    }
    else
    {   
        //crtLoca is placible

        //not place king
        isPossible(State, newX, newY, n, possibleWays);

        //place king
        possibleWays++;
        vector<ll> newState = State;

        newState[crtX] |= (1<<crtY);

        if(crtX == 0)
        {
            newState[crtX+1] |= (1<<crtY);

            if(crtY == 0)
            {
                newState[crtX+1] |= (1<<(crtY+1));
                newState[crtX] |= (1<<(crtY+1));
            }
            else if(crtY == n-1)
            {
                newState[crtX+1] |= (1<<(crtY-1));
                newState[crtX] |= (1<<(crtY-1));
            }
            else
            {
                newState[crtX+1] |= (1<<(crtY-1));
                newState[crtX+1] |= (1<<(crtY+1));
                newState[crtX] |= (1<<(crtY-1));
                newState[crtX] |= (1<<(crtY+1));
            }
        }
        else if(crtX == n-1)
        {
            newState[crtX-1] |= (1<<crtY);

            if(crtY == 0)
            {
                newState[crtX-1] |= (1<<(crtY+1));
                newState[crtX] |= (1<<(crtY+1));
            }
            else if(crtY == n-1)
            {
                newState[crtX-1] |= (1<<(crtY-1));
                newState[crtX] |= (1<<(crtY-1));
            }
            else
            {
                newState[crtX-1] |= (1<<(crtY-1));
                newState[crtX-1] |= (1<<(crtY+1));
                newState[crtX] |= (1<<(crtY-1));
                newState[crtX] |= (1<<(crtY+1));
            }
        }
        else
        {
            newState[crtX+1] |= (1<<crtY);
            newState[crtX-1] |= (1<<crtY);

            if(crtY == 0)
            {
                newState[crtX+1] |= (1<<(crtY+1));
                newState[crtX-1] |= (1<<(crtY+1));
                newState[crtX] |= (1<<(crtY+1));
            }
            else if(crtY == n-1)
            {
                newState[crtX+1] |= (1<<(crtY-1));
                newState[crtX-1] |= (1<<(crtY-1));
                newState[crtX] |= (1<<(crtY-1));
            }
            else
            {
                newState[crtX+1] |= (1<<(crtY+1));
                newState[crtX-1] |= (1<<(crtY+1));
                newState[crtX+1] |= (1<<(crtY-1));
                newState[crtX-1] |= (1<<(crtY-1));
                newState[crtX] |= (1<<(crtY+1));
                newState[crtX] |= (1<<(crtY-1));
            }
        }

        isPossible(newState, newX, newY, n, possibleWays);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin>>n>>k;

    

    vector<ll> initialState(n, 0);
    
    for(int i=0; i<k; i++)
    {
        int x, y;
        cin>>x>>y;

        x--;y--;

        initialState[x] |= (1<<y);
        
    }

    ll possibleWays = 1;

    isPossible(initialState, 0, 0, n, possibleWays);
    
    
    //possibleWays %= MOD;

    cout<<possibleWays<<"\n";

    return 0;
}