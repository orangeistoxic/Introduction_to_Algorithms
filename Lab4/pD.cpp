#include<iostream>
#include<vector>

using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<vector<ll>> dp(n, vector<ll>(n, 0));

    for (int i = 0; i < n; i++)
    {
        cin >> dp[i][i];
    }

    int diff = 2;

    while (diff < n)
    {
        for (int i = 0; i < n - diff; i++)
        {
            int j = i + diff;
            ll temp1 = max(dp[j][j]-dp[i+1][j-1], dp[i+1][i+1]-dp[i+2][j]);
            ll temp2 = max(dp[i][i]-dp[i+1][j-1], dp[j-1][j-1]-dp[i][j-2]);
            dp[i][j] = max(dp[i][i]-temp1, dp[j][j]-temp2);
            //cout<< dp[i][j] << " ";
        }
        diff += 2;
        //cout << "\n";
    }

    if(n%2 == 0)
    {
        cout<< max(-dp[0][n-2] + dp[n-1][n-1], -dp[1][n-1] + dp[0][0]) << "\n";
    }
    else
    {
        cout << dp[0][n-1] << "\n";
    }

    return 0;
}