#include<iostream>
#include<string>
#include<map>

using namespace std;

int main()
{
    int testCase;
    cin>>testCase;
    int numLetters;
    string word;
    map<char,char> ATCG;
    ATCG['A']='T';
    ATCG['T']='A';
    ATCG['C']='G';
    ATCG['G']='C';

    while(testCase--)
    {
        cin>>numLetters;
        cin>>word;
        string opt="";

       for(int i=0;i<numLetters;i++)
       {
           opt+=ATCG[word[i]];
       }
       for(int i=numLetters-1;i>=0;i--)
       {
           cout<<opt[i];
       }
       cout<<endl;
    }
}