#include <iostream>
#include <vector>
#include <iomanip>   // 包含 iomanip 標頭檔案
#include <algorithm> // 包含 max 函數

using namespace std;

// 定義 Fraction 結構體
struct Fraction
{
    long long numerator;
    long long denominator;
};

// 計算分數的值
double calculateFractionValue(long long numerator, long long denominator)
{
    return static_cast<double>(numerator) / denominator;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;
    vector<vector<Fraction>> fractions(N, vector<Fraction>(3));

    // 讀取輸入
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            cin >> fractions[i][j].numerator >> fractions[i][j].denominator;
        }
    }

    // 定義 DP 狀態
    vector<vector<double>> dp(N + 1, vector<double>(N * 1000 + 1, -1.0));
    dp[0][0] = 0.0;

    // 動態規劃轉移
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 0; j <= N * 1000; ++j)
        {
            if (dp[i - 1][j] != -1.0)
            {
                for (int k = 0; k < 3; ++k)
                {
                    long long newNumerator = j + fractions[i - 1][k].numerator;
                    long long newDenominator = i + fractions[i - 1][k].denominator;
                    double newValue = calculateFractionValue(newNumerator, newDenominator);
                    dp[i][newNumerator] = max(dp[i][newNumerator], newValue);
                }
            }
        }
    }

    // 找到最優解
    double maxFractionValue = 0.0;
    for (int j = 0; j <= N * 1000; ++j)
    {
        maxFractionValue = max(maxFractionValue, dp[N][j]);
    }

    // 設置輸出精度
    cout << fixed << setprecision(9) << maxFractionValue << endl;

    return 0;
}