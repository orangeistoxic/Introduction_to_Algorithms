#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm> 


using namespace std;

using ll = long long;
using pii = pair<int, int>;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin>>T;

    while(T--)
    {
        int n;
        cin>>n;

        vector<int> requireDay(n);
        vector<int> penaltyPerDay(n);

        for(int i=0;i<n;i++)
        {
            cin>>requireDay[i];
        }
        for(int i=0;i<n;i++)
        {
            cin>>penaltyPerDay[i];
        }

        vector<pair<float, int>> priority(n);
        for(int i=0;i<n;i++)
        {
            priority[i] = {(float)requireDay[i] / penaltyPerDay[i], i};
        }

        sort(priority.begin(), priority.end());

        for(int i=0; i<n; i++)
        {
            cout<<priority[i].second+1<<" ";
        }
        cout<<endl;

        // ll totalPenalty = 0;
        // int day = 0;

        // for(int i=0; i<n; i++)
        // {
        //     int index = priority[i].second;
           
        //     totalPenalty += penaltyPerDay[index] * day;
        //     day += requireDay[index];
        // }

        // cout<<totalPenalty<<endl;
    }

    return 0;
}