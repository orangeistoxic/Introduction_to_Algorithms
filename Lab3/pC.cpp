#include<iostream>
#include<vector>

using namespace std;

class Point
{
    public:
        vector<int> pTo;
        vector<int> pFrom;
        long long val;
        int start;
        int finish;
        bool isV;
        int belSCC;

        Point()
        {
            val = 0;
            start = -1;
            finish = -1;
            isV = false;
            belSCC = -1;
            
        }

        void Value(long long v, int n)
        {
            val = v;
            pTo.reserve(10);
            pFrom.reserve(10);
            //KEY: Dont reserve too much, it will cause memory error(EK)
        }
        
};

void DFS1(vector<Point> &APs, vector<int> &stack, int loca, int &cnt)
{
    APs[loca].start = cnt;
    cnt++;

    for(int i=0; i<APs[loca].pTo.size(); i++)
    {
        if(APs[APs[loca].pTo[i]].start == -1)
        {
            DFS1(APs, stack, APs[loca].pTo[i], cnt);
        }
    }

    APs[loca].finish = cnt;
    cnt++;
    stack.push_back(loca);
}

void DFS2(vector<Point> &APs, int loca, int &CSCC, long long &totV)
{
    APs[loca].isV = true;
    APs[loca].belSCC = CSCC;
    totV+=APs[loca].val;
    //cout<<"location: "<<loca+1<<" belSCC: "<<CSCC<<" totV: "<<totV<<"\n";

    for(int i=0;i<APs[loca].pFrom.size();i++)
    {
        if(APs[APs[loca].pFrom[i]].isV == false)
        {
            DFS2(APs, APs[loca].pFrom[i], CSCC, totV);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<Point> APs(n);
    for(int i = 0; i < n; i++)
    {
        long long v;
        cin >> v;
        APs[i].Value(v, n);
    }

    for(int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        APs[a-1].pTo.push_back(b-1);
        APs[b-1].pFrom.push_back(a-1);
    }


    //find the SCCs
    vector<int> stack;
    stack.reserve(n);

    int cnt = 0;
    for(int i=0; i<n;i++)
    {
        if(APs[i].start == -1)
        {
            DFS1(APs, stack, i, cnt);
        }
    }

    // for(int i=0; i<n;i++)
    // {
    //     cout<<stack[i]<<" ";
    // }
    // cout<<"\n";

    vector<long long> SCCs;
    SCCs.reserve(n);
    int CSCC = 0;
    for(int i = n-1; i>=0;i--)
    {
        if(APs[stack[i]].isV == false)
        {
            long long totV = 0;
            DFS2(APs, stack[i], CSCC, totV);
            CSCC++;
            SCCs.push_back(totV);
        }
    }

    
    // for(int i = 0; i<APs[3].pTo.size(); i++)
    // {
    //     cout << APs[3].pTo[i] << " ";
    // }
    // cout << "\n";
    

    for(int i = 0; i < n; i++)
    {
        cout << SCCs[APs[i].belSCC] << " ";
    }
    cout << "\n";

    return 0;
}