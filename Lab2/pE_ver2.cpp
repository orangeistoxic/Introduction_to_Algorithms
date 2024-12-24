#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

const long long MOD = 998244353;

vector<int> MergeSort(vector<int> arr, int l, int r, long long &setInversions)
{
    if(l<r)
    {
        int m=((l+r)/2)+1;
        vector<int> arrl, arrr;
        arrl.assign(arr.begin() + l, arr.begin() + m);
        arrr.assign(arr.begin() + m, arr.begin() + r + 1);
        vector<int> L = MergeSort(arrl, 0, arrl.size()-1, setInversions);
        vector<int> R = MergeSort(arrr, 0, arrr.size()-1, setInversions);

        int i = 0, j = 0, k = l;
        
        while(i < L.size() && j < R.size())
        {
            if(L[i] <= R[j])
            {
                arr[k] = L[i];
                i++;
            }
            else
            {
                arr[k] = R[j];
                j++;
                setInversions += L.size() - i;
            }
            k++;
        }

        while(i < L.size())
        {
            arr[k] = L[i];
            i++;
            k++;
        }
        while(j < R.size())
        {
            arr[k] = R[j];
            j++;
            k++;
        }

        return arr;

    }
    else
    {
        return arr;
    }
}

pair<int, int> SmallerAndLarger(vector<int> sortedArr, int ele)
{
    int small = lower_bound(sortedArr.begin(), sortedArr.end(), ele) - sortedArr.begin();
    // int large = sortedArr.end() - upper_bound(sortedArr.begin(), sortedArr.end(), ele);
    int large = 0;
    for (int i = small + 1; i < sortedArr.size(); i++)
    {
        if (sortedArr[i] != ele)
        {
            large = sortedArr.size() - i;
            break;
        }
    }

    return pair<int, int>{small, large};
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    long long k;
    cin >> n >> k;
    vector<int> oriArr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> oriArr[i];
    }

    long long setInversions = 0, totalInversions = 0, setsInversions = 0;

    // sort array and count inversions in a set
    vector<int> sortedArr = MergeSort(oriArr, 0, n - 1, setInversions);
    

    // cout<<setInversions<<endl;
    // for(int i=0;i<n;i++)
    // {
    //     cout<<sortedArr[i]<<" ";
    // }

    // count inversions in set to set (setsInversions)
    //  for (int i = n - 1; i >= 0; i--)
    //  {
    //      setsInversions += lower_bound(sortedArr.begin(), sortedArr.end(), oriArr[i]) - sortedArr.begin();
    //  }
    // cout<<"setsInverions: "<<setsInversions<<endl;

    // count iteration
    long long numRepeat = (k / n) % MOD;

    int nonRepeat = k % n;

    if (numRepeat == 0)
    {
        for (int i = 0; i < nonRepeat; i++)
        {
            totalInversions += (setInversions);
            pair<int, int> numMinusAndPlus = SmallerAndLarger(sortedArr, oriArr[i]);
            setInversions = (setInversions + numMinusAndPlus.second - numMinusAndPlus.first);

            setsInversions += numMinusAndPlus.first;
        }
        for (int i = nonRepeat; i < n; i++)
        {
            setsInversions += lower_bound(sortedArr.begin(), sortedArr.end(), oriArr[i]) - sortedArr.begin();
        }
    }
    else
    {
        long long cycletot = 0;
        for (int i = 0; i < nonRepeat; i++)
        {
            totalInversions += (setInversions);
            cycletot += (setInversions);
            pair<int, int> numMinusAndPlus = SmallerAndLarger(sortedArr, oriArr[i]);
            setInversions = (setInversions + numMinusAndPlus.second - numMinusAndPlus.first);

            setsInversions += numMinusAndPlus.first;
        }
        for (int i = nonRepeat; i < n; i++)
        {
            cycletot += (setInversions);
            pair<int, int> numMinusAndPlus = SmallerAndLarger(sortedArr, oriArr[i]);
            setInversions = (setInversions + numMinusAndPlus.second - numMinusAndPlus.first);

            setsInversions += numMinusAndPlus.first;
        }
        totalInversions = ((totalInversions % MOD) + ((numRepeat * (cycletot % MOD)) % MOD)) % MOD;
        // cout<<"cycletot: "<<cycletot<<endl;
    }
    setsInversions = setsInversions % MOD;
    totalInversions += (setsInversions * (((k - 1) % MOD) * (k % MOD) / 2) % MOD) % MOD;
    totalInversions %= MOD;

    cout << totalInversions << endl;

    return 0;
}