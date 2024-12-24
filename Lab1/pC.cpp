#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

bool checkLengthIsPossible(int length, vector<int> &redStonePath, vector<int> &statue)
{
   vector<int> statueRemain = statue;
   bool foundHead = false;
   int currentStatue = 0;
   for(int i = 0; i < redStonePath.size(); i++)
   {
        if(foundHead)
        {
            if(redStonePath[i] >= length)
            {
                statueRemain[currentStatue] --;
                if(statueRemain[currentStatue] == 0)
                {
                    if(currentStatue == statue.size() - 1)
                    {
                        return true;
                    }
                    else
                    {
                        currentStatue++;
                        foundHead = false;
                    }
                }
            }
            else
            {
                foundHead = false;
                statueRemain[currentStatue] = statue[currentStatue];
            }
        }
        else
        {
            if(redStonePath[i] >= length)
            {
                foundHead = true;
                statueRemain[currentStatue] --;
                if(statueRemain[currentStatue] == 0)
                {
                    if(currentStatue == statue.size() - 1)
                    {
                        return true;
                    }
                    else
                    {
                        currentStatue++;
                        foundHead = false;
                    }
                }
            }
            else
            {
                continue;
            }
        }
   }

    return false;
    
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, K;
    cin>>N>>K;
    vector<int> redStonePath;
    
    int longestPath = 0;
    for(int i = 0; i < N; i++)
    {
        int path;
        cin>>path;
        redStonePath.push_back(path);
        
        longestPath = max(longestPath, path);
    }

    

    vector<int> statue(K);
    int totRedStoneNeed = 0;
    for(int i = 0; i < K; i++)
    {
        int size;
        cin>>size;
        statue[i] = size;
        totRedStoneNeed += size;
    }

    if(totRedStoneNeed > N)
    {
        cout<<0<<endl;
    }
    else
    {
        //choose a num between 1 and longestPath(maybe longestPath/2), check if possible
        //if so, check right side of longestPath/2 
        //if not, check left side of longestPath/2
        // do this until left side = right side

        int left = 1;
        int right = longestPath;
        int check = (left + right)/2;
        while(left < right -1)
        {
            if(checkLengthIsPossible(check, redStonePath, statue))
            {
                //cout<<check<< " is possible"<<endl;
                left = check;
            }
            else
            {
                //cout<<check<< " is not possible"<<endl;
                right = check;
            }
            check = (left + right)/2;
            //cout<<left<<" "<<right<<endl;
        }

        if(checkLengthIsPossible(right, redStonePath, statue))
        {
            cout<<right<<endl;
        }
        else
        {
            cout<<left<<endl;
        }

        // for(int i=0;i<redStonePath.size();i++)
        // {
        //     cout<<redStonePath[i]<<" ";
        // }
        // cout<<endl;
        // for(int i=0;i<statue.size();i++)
        // {
        //     cout<<statue[i]<<" ";
        // }

        
    }



    return 0;

}