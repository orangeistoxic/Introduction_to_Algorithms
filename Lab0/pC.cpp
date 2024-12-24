#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

bool IsMagnetInThisQueue(priority_queue<int> q,int magnet)
{
    while(!q.empty())
    {
        if(q.top()==magnet)
        {
            return true;
        }
        q.pop();
    }
    return false;
}

int main()
{
    int numMagnet;
    cin>>numMagnet;
    priority_queue<int> piles[numMagnet]; 
    int totHappy=0;

    for(int i=0;i<numMagnet;i++)
    {
        piles[i].push(i+1);
    }
    int numConbine=numMagnet-1;
    int magnet1,magnet2;
    int pile1,pile2;
    while(numConbine--)
    {
        cin>>magnet1>>magnet2;
        for(int i=0;i<numMagnet;i++)
        {
            if(!magnet1 < piles[i].top())
            {
                bool ismagnetfound=IsMagnetInThisQueue(piles[i],magnet1);
                if(ismagnetfound)
                {
                    pile1=i;
                    break;
                }
            }

            
        }
        for(int i=0;i<numMagnet;i++)
        {
            if (!magnet2 < piles[i].top())
            {
                bool ismagnetfound = IsMagnetInThisQueue(piles[i], magnet2);
                if (ismagnetfound)
                {
                    pile2 = i;
                    break;
                }
            }
        }

        int pileSize=max(piles[pile1].size(),piles[pile2].size());
        priority_queue<int> newPile;
        for(int i=0;i<pileSize;i++)
        {
            if(piles[pile1].empty())
            {
                totHappy+=piles[pile2].top();
                //cout<<"Gain Happy: "<<piles[pile2].top()<<endl;
                newPile.push(piles[pile2].top());
                piles[pile2].pop();
            }
            else if(piles[pile2].empty())
            {
                totHappy+=piles[pile1].top();
                //cout<<"Gain Happy: "<<piles[pile1].top()<<endl;
                newPile.push(piles[pile1].top());
                piles[pile1].pop();
            }
            else
            {
                totHappy+=piles[pile1].top()*piles[pile2].top();
                //cout<<"Gain Happy: "<<piles[pile1].top()*piles[pile2].top()<<endl;
                newPile.push(piles[pile1].top());
                newPile.push(piles[pile2].top());
                piles[pile1].pop();
                piles[pile2].pop();
            }
        }
        piles[pile1]=newPile;

        if (totHappy >= 998244353)
        {
            totHappy = totHappy % 998244353;
        }
    }    
    cout<<totHappy<<endl;

    return 0;
}