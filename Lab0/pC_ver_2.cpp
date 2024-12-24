#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

int main()
{
    int numMagnet;
    cin>>numMagnet;
    long long int totHappy=0;

    int MagnetLocation[numMagnet];
    priority_queue<int> piles[numMagnet];

    for(int i=0;i<numMagnet;i++)
    {
        piles[i].push(i+1);
        MagnetLocation[i]=i;
    }

    int numConbine = numMagnet - 1;
    int magnet1, magnet2;
    int pile1, pile2;

    while(numConbine--)
    {
        cin>>magnet1>>magnet2;
        pile1=MagnetLocation[magnet1-1];
        pile2=MagnetLocation[magnet2-1];

        int pileSize = max(piles[pile1].size(), piles[pile2].size());
        priority_queue<int> newPile;

        for (int i = 0; i < pileSize; i++)
        {
            if (piles[pile1].empty())
            {
                totHappy += piles[pile2].top();

                //cout<<"Gain Happy: "<<piles[pile2].top()<<endl;

                MagnetLocation[piles[pile2].top()-1]=pile1;
                newPile.push(piles[pile2].top());
                piles[pile2].pop();
            }
            else if (piles[pile2].empty())
            {
                totHappy += piles[pile1].top();

                //cout<<"Gain Happy: "<<piles[pile1].top()<<endl;

                newPile.push(piles[pile1].top());
                piles[pile1].pop();
            }
            else
            {
                totHappy += (long long)piles[pile1].top() * piles[pile2].top();

                //cout<<"Gain Happy: "<<piles[pile1].top()*piles[pile2].top()<<endl;

                MagnetLocation[piles[pile2].top() - 1] = pile1;
                newPile.push(piles[pile1].top());
                newPile.push(piles[pile2].top());
                piles[pile1].pop();
                piles[pile2].pop();
            }

           if(totHappy>=998244353)
           {
                totHappy%=998244353;
           }
        }

        piles[pile1] = newPile;
    }

    cout<<totHappy<<endl;
}