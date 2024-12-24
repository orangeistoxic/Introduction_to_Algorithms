#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>

using namespace std;

const long long MOD = 998244353;

void Merge(vector<int> &arr,int l, int m, int r, long long &setInversions)
{
    int nl = m - l;
    int nr = r - m + 1;

    vector<int> L(nl), R(nr);

    // for(int i = 0; i < nl; i++)
    // {
    //     L[i] = arr[l + i];
    // }
    // for(int i = 0; i < nr; i++)
    // {
    //     R[i] = arr[m + i];
    // }

    L.assign(arr.begin() + l, arr.begin() + m);
    R.assign(arr.begin() + m, arr.begin() + r + 1);

    int i = 0, j = 0, k = l;

    while(i < nl && j < nr)
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
            setInversions += nl - i;
        }
        k++;
    }
    while(i < nl)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while(j < nr)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void MergeSort(vector<int> &arr, int left, int right, long long &setInversions)
{
    if(left < right)
    {
        int mid = ((left + right) / 2) + 1;
        MergeSort(arr, left, mid-1, setInversions);
        MergeSort(arr, mid, right, setInversions);
        Merge(arr, left, mid, right, setInversions);
    }
}

pair<int, int> SmallerAndLarger(vector<int> &sortedArr, int ele)
{
    int small = lower_bound(sortedArr.begin(), sortedArr.end(), ele) - sortedArr.begin();
    int large = sortedArr.end() - upper_bound(sortedArr.begin(), sortedArr.end(), ele);
    

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
    for(int i = 0; i < n; i++)
    {
        cin >> oriArr[i];
    }

    long long setInversions = 0, totalInversions = 0,setsInversions = 0;
    
    //sort array and count inversions in a set
    vector<int> sortedArr = oriArr;
    MergeSort(sortedArr, 0, n-1,setInversions);

    // cout<<setInversions<<endl;
    // for(int i=0;i<n;i++)
    // {
    //     cout<<sortedArr[i]<<" ";
    // }

    //count inversions in set to set (setsInversions)
    // for (int i = n - 1; i >= 0; i--)
    // {
    //     setsInversions += lower_bound(sortedArr.begin(), sortedArr.end(), oriArr[i]) - sortedArr.begin();
    // }
    //cout<<"setsInverions: "<<setsInversions<<endl;
    

    //count iteration
    long long numRepeat=(k/n)%MOD;

    int nonRepeat = k % n;

    if(numRepeat==0)
    {
        for (int i = 0; i < nonRepeat; i++)
        {
            totalInversions = (totalInversions + setInversions)%MOD;
            pair<int, int> numMinusAndPlus = SmallerAndLarger(sortedArr, oriArr[i]);
            setInversions =(setInversions + numMinusAndPlus.second - numMinusAndPlus.first);

            setsInversions = (setsInversions + numMinusAndPlus.first) % MOD;
        }
        for(int i=nonRepeat;i<n;i++)
        {
            setsInversions += lower_bound(sortedArr.begin(), sortedArr.end(), oriArr[i]) - sortedArr.begin();
            setsInversions = setsInversions % MOD;
        }
    }
    else
    {
        long long cycletot=0;
        for (int i = 0; i < nonRepeat; i++)
        {
            totalInversions = (totalInversions + setInversions) % MOD;
            cycletot = (cycletot + setInversions) % MOD;
            pair<int, int> numMinusAndPlus = SmallerAndLarger(sortedArr, oriArr[i]);
            setInversions = (setInversions + numMinusAndPlus.second - numMinusAndPlus.first);

            setsInversions = (setsInversions + numMinusAndPlus.first)%MOD;
        }
        for (int i = nonRepeat; i < n; i++)
        {
            cycletot = (cycletot + setInversions) % MOD;
            pair<int, int> numMinusAndPlus = SmallerAndLarger(sortedArr, oriArr[i]);
            setInversions = (setInversions + numMinusAndPlus.second - numMinusAndPlus.first);

            setsInversions = (setsInversions + numMinusAndPlus.first) % MOD;
        }
        totalInversions = ((totalInversions%MOD) + ((numRepeat * (cycletot%MOD)) % MOD))%MOD;
        //cout<<"cycletot: "<<cycletot<<endl;
    }
    setsInversions = setsInversions % MOD;
    totalInversions += (setsInversions * ((((k - 1) % MOD) * (k % MOD) / 2) % MOD)) % MOD;
    totalInversions %= MOD;

    cout<<totalInversions<<endl; 

    return 0;
}