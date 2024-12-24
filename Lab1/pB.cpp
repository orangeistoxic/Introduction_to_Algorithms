#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, L;
    cin >> N >> L;
    vector<int> v(L);
    int *vLoca=new int[N];

    for(int i = 0; i < N; i++)
    {
        int loca;
        cin >> loca;
        vLoca[i] = loca-1;
    }

    

    for(int i = 0; i < N; i++)
    {
        int range;
        cin >> range;

        int left = max(0, vLoca[i] - range);
        int right = min(vLoca[i] + range, L-1);

        v[left]++;
        v[right+1]--;
    }

    int maxPeople = v[0];
    int maxLoca = 0;

    for(int i = 1; i < L; i++)
    {
        v[i] += v[i-1]; 
        if(v[i] > maxPeople)
        {
            maxPeople = v[i];
            maxLoca = i;

        }
         
    }

    cout << maxLoca + 1 << " " << maxPeople << endl;
    
    return 0;
}