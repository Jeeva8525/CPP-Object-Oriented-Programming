#include <iostream>
using namespace std;
class Solution {
public:
    string countAndSay(int n)
    {
        if(n<=1)
            return "1";
        else
        {
            string temp=countAndSay(n-1)+"  ",ret="";
            int s=temp.size()-2;
            char c;
            int y;
            for(int x=0;x<s;x=y)
            {
                c=49;//ascii of '1'
                for(y=x+1;temp[x]==temp[y];y++)
                {
                        c+=1;
                }
                ret=ret+c+temp[x];
            }
            return ret;
        }
    }
};
int main()
{
    Solution s1;
    int n=0;
    cout<<"Enter the number to countAndSay(): ";
    cin>>n;
    for(int x=1;x<=n;x++)
    {
        cout<<"Value of countAndSay("<<x<<") is "<<s1.countAndSay(x)<<endl;
    }
}
