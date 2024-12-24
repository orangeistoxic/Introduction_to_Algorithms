#include<iostream>
#include<vector>

using namespace std;

vector<int> Rebuild(vector<int> &preOrder, int l, int r)
{
    if(l == r)
    {
        return {preOrder[l]};
    }

    vector<int> root = {preOrder[l]};
    
    int lPreSt = l + 1;
    int rPreSt = l + 1;
    for(int i = l + 1; i <= r; i++)
    {
        if(preOrder[i] < root[0])
        {
            rPreSt++;
        }
        else
        {
            break;
        }
    }

    if(rPreSt > r)
    {
        // that mean there is no right subtree
        vector<int> res = Rebuild(preOrder, lPreSt, r);
        res.insert(res.end(), root.begin(), root.end());
        return res;
    }
    else if(rPreSt == l + 1)
    {
        // that mean there is no left subtree
        vector<int> res = Rebuild(preOrder, rPreSt, r);
        res.insert(res.end(), root.begin(), root.end());
        return res;
    }
    else
    {
        vector<int> res = Rebuild(preOrder, lPreSt, rPreSt - 1);
        vector<int> right = Rebuild(preOrder, rPreSt, r);
        res.insert(res.end(), right.begin(), right.end());
        res.insert(res.end(), root.begin(), root.end());
        return res;
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
        vector<int> postOrder;
        postOrder.reserve(n);
        postOrder = Rebuild(preOrder, 0, n-1);

        for(int i = 0; i < n; i++)
        {
            cout << postOrder[i] << " ";
        }
        cout << "\n";

    return 0;
}