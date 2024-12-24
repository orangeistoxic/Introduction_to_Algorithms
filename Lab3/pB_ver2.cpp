#include<iostream>
#include<vector>
#include<stack>

using namespace std;

void DFS(vector<int> &preOrder, int l, int r, vector<int> &st)
{

    st.push_back(preOrder[l]);
    if(l >= r)
    {
        return;
    }
    
    int mid = (l+1+r)/2;
    bool isFindRightStart = false;
    while(!isFindRightStart)
    {

        if(preOrder[mid] > preOrder[l])
        {
            if(preOrder[mid-1] < preOrder[l]) //find the right subtree(maybe left subtree is empty)
            {
                isFindRightStart = true;
                DFS(preOrder, mid, r, st);
                DFS(preOrder, l+1, mid-1, st);
            }
            else if(preOrder[mid-1] == preOrder[l])
            {
                isFindRightStart = true;
                DFS(preOrder, mid, r, st);
            }
            else
            {
                mid = (l+1 + mid)/2;
            }
        }
        else if(mid == r) //no right subtree
        {
            isFindRightStart = true;
            DFS(preOrder, l+1, r, st);
        }
        else
        {
            mid = (mid + r+1)/2;
        }
       
        
    }

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> preOrder(n);
    for(int i = 0; i < n; i++)
    {
        cin >> preOrder[i];
    }
    
    vector<int> st;
    st.reserve(n);
    DFS(preOrder, 0, n - 1, st);

    for(int i = n-1; i>=0; i--)
    {
        cout << st[i] << " ";
    }
    cout << endl;
    return 0;
}