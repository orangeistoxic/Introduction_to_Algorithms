#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

bool decrement(long long a, long long b)
{
    return a > b;
}

bool checkTimePossible(long long checkTime, vector<long long> &difficulty, vector<long long> &time, long long &K)
{
    vector<long long> originalTime = time;
    long long originalK = K;

    //cout<<"checkTime= "<<checkTime<<"--------"<<endl;

    for (int i = 0; i < time.size(); i++)
    {
        if(time[i] > checkTime)
        {
            long long diff = time[i] - checkTime;
            long long needK = ceil((float)diff / difficulty[i]);
            K -= needK;
            time[i] -= needK * difficulty[i];
            //cout<<"K= "<<K<<endl;
            if(K < 0)
            {
                K = originalK;
                time = originalTime;
                //cout<<"-------"<<endl;
                return false;
            }
        }
    }
    //cout<<"-------"<<endl;
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n, K;
    cin >> n >> K;
    vector<long long> power(n);
    vector<long long> difficulty(n);


    for (int i = 0; i < n; i++)
    {
        cin >> power[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> difficulty[i];
    }


    sort(power.begin(), power.end());
    sort(difficulty.begin(), difficulty.end(), decrement);

    // for(int i = 0; i < n; i++)
    // {
    //     cout<<power[i]<<" ";
    // }
    // cout<<endl;
    // for(int i = 0; i < n; i++)
    // {
    //     cout<<difficulty[i]<<" ";
    // }
    // cout<<endl;

    vector<long long> time(n);
    long long minTime = 0;
    long long maxTime = 0;
    for (int i = 0; i < n; i++)
    {
        
        time[i] = power[i] * difficulty[i];
        maxTime = max(maxTime, time[i]);
    }

    long long check = minTime + (maxTime - minTime) / 2;

    while (minTime < maxTime - 1)
    {
        if (checkTimePossible(check, difficulty, time, K))
        {
            maxTime = check;
        }
        else
        {
            minTime = check + 1;
        }

        check = minTime + (maxTime - minTime) / 2;
    }

    if (checkTimePossible(minTime, difficulty, time, K))
    {
        cout << minTime << endl;
    }
    else
    {
        cout << maxTime << endl;
    }

    return 0;
}