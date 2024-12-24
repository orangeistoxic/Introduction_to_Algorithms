#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_set>

using namespace std;

using ll = long long;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);


    int n,Q;
    cin >> n >> Q;

    vector<int> classes(n);
    vector<ll> score(n);

    for(int i=0;i<n;i++)
    {
        cin>>classes[i];
    }

    // cout<<"Classes input done"<<endl;
    // for(int i=0;i<n;i++)
    // {
    //     cout<<classes[i]<<" ";
    // }
    // cout<<endl;

    for(int i=0;i<n;i++)
    {
        cin>>score[i];
        score[i] = score[i]* classes[i];
    }

    while(Q--)
    {
        int l,r;
        cin>>l>>r;
        l--;r--;

        ll sum = 0;
        

        unordered_set<int> allClasses;
        

        for(int i=l;i<=r;i++)
        {
            allClasses.insert(classes[i]);
        }

        

        for(auto c:allClasses)
        {
            ll maxScore = 0;
            for(int i=l;i<=r;i++)
            {
                if(classes[i] == c)
                {
                    //cout<<"found one"<<endl;
                    maxScore = max(maxScore,score[i]);
                }
            }
            sum += maxScore;
        }

        cout<<sum<<endl;
    }

    return 0;
}