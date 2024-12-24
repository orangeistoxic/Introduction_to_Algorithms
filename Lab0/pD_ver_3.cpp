#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int QuickSelect(int *arr, int l, int r, int k)
{
    nth_element(arr + l, arr + k, arr + r + 1);
    return arr[k];
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;

    int *arr = new int[N];
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }

    int medianLoca;
    if (N % 2 == 0)
    {
        medianLoca = N / 2 - 1;
    }
    else
    {
        medianLoca = N / 2;
    }

    int median = QuickSelect(arr, 0, N - 1, medianLoca);

    cout << median << endl;
}