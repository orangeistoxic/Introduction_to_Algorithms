#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, X;
    cin >> n >> X;

    vector<int> price(n), coffee(n), amount(n), dp(X + 1, 0);
    for(int i=0; i<n; i++)
    {
        cin >> price[i];
    }
    for(int i=0; i<n; i++)
    {
        cin >> coffee[i];
    }
    for(int i=0; i<n; i++)
    {
        cin >> amount[i];
    }

    for(int i=0; i<n; i++)
    {
        int k = 1;
        while(amount[i] > 0)
        {
            int a = min(k, amount[i]);
            for(int j=X; j>=price[i]*a; j--)
            {
                dp[j] = max(dp[j], dp[j - price[i]*a] + coffee[i]*a);
            }
            amount[i] -= a;
            k *= 2;
        }
    }

    cout << dp[X] << "\n";

    return 0;
}
