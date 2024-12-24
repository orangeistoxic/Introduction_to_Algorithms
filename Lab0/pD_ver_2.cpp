#include<iostream>
#include<algorithm>
#include<vector>
#include<queue> 

using namespace std;

int QuickSelect(int* arr,int l,int r,int k)
{
    if(l==r) //only one element
    {
        return arr[l];
    }
    
    int pivot = r;
    int pivotValue = arr[pivot];
    int firstLarger = l;

    for(int i=l;i<r;i++)
    {
        if(arr[i]<pivotValue)
        {
            swap(arr[i],arr[firstLarger]);
            firstLarger++;
        }
    }
    swap(arr[pivot],arr[firstLarger]);
    pivot = firstLarger;

    // cout << "pivot: " << pivot << ",pivotValue: " << pivotValue << endl;
    // for(int i=l;i<=r;i++)
    // {
    //     cout << arr[i] << " " ;
    // }
    // cout << endl;

    if(pivot==k)
    {
        return arr[pivot];
    }
    else if(pivot>k)
    {
        return QuickSelect(arr,l,pivot-1,k);
    }
    else
    {
        return QuickSelect(arr,pivot+1,r,k);
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;

    int* arr=new int[N];
    for(int i=0;i<N;i++)
    {
        cin >> arr[i];
    }

    int medianLoca;
    if(N%2==0)
    {
        medianLoca = N/2-1;
    }
    else
    {
        medianLoca = N/2;
    }
    
    
    int median = QuickSelect(arr,0,N-1,medianLoca);

    cout << median << endl;
    

}