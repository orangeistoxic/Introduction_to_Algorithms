#include<iostream>
#include<algorithm>
#include<vector>
#include<set>

using namespace std;

int MinimumMedianSum(pair<int,int>* arr, int index)
{
    int minMedianSum=-1;
    multiset<int> sortedArr;
    for(int i=index;i>0;i--)
    {
        sortedArr.insert(arr[i].first);
        int median=arr[i-1].second;
        auto it =sortedArr.begin();
        if(sortedArr.size()%2==0)
        {
            advance(it, sortedArr.size() / 2 - 1);
            median += *it;
        }
        else
        {
            advance(it, sortedArr.size() / 2);
            median += *it;
        }

        if(minMedianSum==-1 || median<minMedianSum)
        {
            minMedianSum=median;
        }
    }
    sortedArr.insert(arr[0].first);
    int median = 0;
    auto it = sortedArr.begin();
    if (sortedArr.size() % 2 == 0)
    {
        advance(it, sortedArr.size() / 2 - 1);
        median += *it;
    }
    else
    {
        advance(it, sortedArr.size() / 2);
        median += *it;
    }

    if (minMedianSum == -1 || median < minMedianSum)
    {
        minMedianSum = median;
    }

    return minMedianSum;

}

//Given a array of integers, find the minimun sum of median of all subarrays
int main()
{
    int numElements;
    cin>>numElements;
    pair<int,int> *arr = new pair<int,int>[numElements]; //first is the value, second is the minimum sum of median of all subarrays that ends at this element
    for(int i=0;i<numElements;i++)
    {
        cin>>arr[i].first;
        arr[i].second=0;
    }

    for(int i=0;i<numElements;i++)
    {
        arr[i].second = MinimumMedianSum(arr,i);
    }

    cout<<arr[numElements-1].second<<endl;

    return 0;
}