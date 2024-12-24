#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void PrintResult(vector<vector<int>> &DV, int step, vector<bool> &isStable)
{
    cout<<"X | "<<"A | "<<"B | "<<"C | "<<"D | "<<"E | "<<"F | "<< "Step: "<<step<<"\n";
    cout<<"-----------------------------------------------------------------\n";

    for(int i=0; i<6; i++)
    {
        cout<<char('A'+i)<<" | ";
        for(int j=0; j<6; j++)
        {
            if(DV[i][j] == 100)
            {
                cout<<"- | ";
            }
            else
            {
                cout<<DV[i][j]<<" | ";
            }
        }

        if(isStable[i])
        {
            cout<<"Stable\n";
        }
        else
        {
            cout<<"Not Stable\n";
        }
    }

    cout << "-----------------------------------------------------------------\n";
}   

int main()
{


    vector<vector<int>> DV(6, vector<int>(6, 100));
    vector<vector<int>> DV2(6, vector<int>(6, 100));

    DV[0][0] = 0;
    DV[0][1] = 3;
    DV[0][3] = 1;

    DV[1][1] = 0;
    DV[1][0] = 3;
    DV[1][2] = 1;
    DV[1][3] = 1;


    DV[2][2] = 0;
    DV[2][1] = 1;
    DV[2][3] = 3;
    DV[2][4] = 1;

    DV[3][3] = 0;
    DV[3][0] = 1;
    DV[3][1] = 1;
    DV[3][2] = 3;
    DV[3][5] = 6;

    DV[4][4] = 0;
    DV[4][2] = 1;
    DV[4][5] = 1;

    DV[5][5] = 0;
    DV[5][3] = 6;
    DV[5][4] = 1;
    

    vector<bool> isStable(6, 0);

    int step = 1;

    DV2 = DV;

    bool isAllStable = 0;

    PrintResult(DV, step, isStable);

    while(!isAllStable)
    {
        isAllStable = 1;
        for(int i=0; i<6; i++)
        {
            isStable[i] = 1;

            for(int j=0; j<6; j++)
            {
                if(i ==j || DV[i][j] == 100)
                {
                    continue;
                }

                for(int k=0; k<6; k++)
                {
                    if(i == k || j == k || DV[j][k] == 100)
                    {
                        continue;
                    }

                    if(DV[i][j] + DV[j][k] < DV2[i][k])
                    {
                        DV2[i][k] = DV[i][j] + DV[j][k];
                        isStable[i] = 0;
                        isAllStable = 0;
                    }
                }
            }
        }

        DV = DV2;

        PrintResult(DV, ++step, isStable);
    }

    system("pause");

    return 0;
}