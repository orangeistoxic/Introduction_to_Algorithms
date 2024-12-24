#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

const long long MOD=1000000007;

vector<vector<long long>> Mat_Mult4(vector<vector<long long>> A,vector<vector<long long>> B)
{
    vector<vector<long long>> C(4,vector<long long>(4,0));
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            for(int k=0;k<4;k++)
            {
                C[i][j]=(C[i][j]+A[i][k]*B[k][j])%MOD;
            }
        }
    }
    return C;
}

vector<vector<long long>> Mat_Mult3(vector<vector<long long>> A,vector<vector<long long>> B)
{
    vector<vector<long long>> C(3,vector<long long>(3,0));
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            for(int k=0;k<3;k++)
            {
                C[i][j]=(C[i][j]+A[i][k]*B[k][j])%MOD;
            }
        }
    }
    return C;
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int k,s;
    cin>>k>>s;
    
    if(s==0)
    {
        while (k--)
        {
            long long x1, x2, a, b, c;
            long long n;
            cin >> x1 >> x2 >> a >> b >> c >> n;
            vector<vector<long long>> matrix(3, vector<long long>(3, 0));
            matrix[0][0] = a;
            matrix[0][1] = b;
            matrix[0][2] = c;
            matrix[1][0] = 1;
            matrix[2][2] = 1;

            vector<vector<long long>> res(3, vector<long long>(3, 0));
            for (int i = 0; i < 3; i++)
            {
                res[i][i] = 1;
            }

            n -= 2;

            while (n > 0)
            {
                if (n % 2 == 1)
                {
                    res = Mat_Mult3(res, matrix);
                }
                matrix = Mat_Mult3(matrix, matrix);
                n /= 2;
            }

            cout << (res[0][0] * x2 + res[0][1] * x1 + res[0][2]) % MOD << " 0" <<endl;
        }
    }
    else //s==1
    {
        while(k--)
        {
            long long x1,x2,a,b,c;
            long long n;
            cin>>x1>>x2>>a>>b>>c>>n;

            long long S2=x1+x2;
            vector<vector<long long>> matrix(4,vector<long long>(4,0));
            matrix[0][0]=a;
            matrix[0][1]=b;
            matrix[0][2]=c;
            matrix[1][0]=1;
            matrix[2][2]=1;
            matrix[3][0]=a;
            matrix[3][1]=b;
            matrix[3][2]=c;
            matrix[3][3]=1;

            vector<vector<long long>> res(4,vector<long long>(4,0));
            for(int i=0;i<4;i++)
            {
                res[i][i]=1;
            }
            n-=2;

            while(n>0)
            {
                if(n%2==1)
                {
                    res=Mat_Mult4(res,matrix);
                }
                matrix=Mat_Mult4(matrix,matrix);
                n/=2;
            }

            cout<<(res[0][0]*x2+res[0][1]*x1+res[0][2])%MOD<<" "<<(res[3][0]*x2+res[3][1]*x1+res[3][2]+S2)%MOD<<endl;
        }
    }

    return 0;
}