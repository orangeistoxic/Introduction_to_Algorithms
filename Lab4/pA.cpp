#include<iostream>
#include<vector>
#include<cmath>
#include<string>

using namespace std;

using ll = long long;

int main()
{
    //LCS Problem
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int k;
    cin>>k;

    while(k--)
    {
        int s1leng, s2leng;
        string s1, s2;
        cin>>s1leng>>s2leng>>s1>>s2;

        vector<vector<int>> dp(s1leng+1, vector<int>(s2leng+1, 0));//location+1 is dp location
        for(int i=1;i<=s1leng; i++)
        {
            for(int j=1;j<=s2leng;j++)
            {
                if(s1[i-1]  == s2[j-1])
                {
                    dp[i][j] = dp[i-1][j-1]+1;
                }
                else
                {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }

        cout<<dp[s1leng][s2leng]<<endl;

    }

    return 0;
}