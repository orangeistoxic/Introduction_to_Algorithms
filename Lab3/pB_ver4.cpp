#include<iostream>
#include<vector>
#include<stack>
#include <climits>

typedef long long ll;

using namespace std;

void FindPostOrder(vector<ll> &preOrder, int n, int minV, int maxV, int &index, vector<ll> &postOrder, bool &isValid)
{
    //if index == n, that mean we have traversed the whole preOrder array
    if(index == n)
    {
        return ;
    }

    //if the current element is not in the range of minV and maxV, that mean it is not in the current subtree
    if(preOrder[index] >= maxV || preOrder[index] <= minV)
    {
        return ;
    }
    

    ll value = preOrder[index];
    index++;

    // if in left
    FindPostOrder(preOrder, n, minV, value, index, postOrder, isValid);

    // if in right
    FindPostOrder(preOrder, n, value, maxV, index, postOrder, isValid);

    postOrder.push_back(value);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<ll> preOrder(n);
    for(int i = 0; i < n; i++)
    {
        cin >> preOrder[i];
    }
    
    int index = 0;
    vector<ll> postOrder;
    postOrder.reserve(n);
    postOrder[n-1] = -1;
    bool isValid = true;
    
    FindPostOrder(preOrder, n, INT_MIN, INT_MAX, index, postOrder, isValid);

    // for (int i = 0; i < n; i++)
    // {
    //     cout << postOrder[i] << " ";
    // }
    // cout << "\n";

    if(postOrder[n-1] < 0)
    {
        cout << -1 << "\n";
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            cout << postOrder[i] << " ";
        }
        cout << "\n";
    }

    return 0;
}