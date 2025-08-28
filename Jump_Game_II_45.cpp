/* 
Jump Game - 2 (LeetCode Problem - 45)
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
public:
    int jump(vector<int>& nums)
    {
        int ct=0;
        for(auto it=nums.begin();it!=nums.end()-1;)
        {
            for(int x=1;x<=*it;x++)
            {
                if(it+x==nums.end()-1)
                {
                    ct++;
                    cout<<"Jump to "<<*(it+x)<<endl;
                    return ct;
                }
            }
            int high=0,diff=it-nums.begin();
            int last=*it;
            for(int x=diff+1;x<=diff+last;x++)
            {
                if(high<=(nums[x]+x-(diff+1)))
                {
                    high=nums[x]+x-(diff+1);
                    it=nums.begin()+x;

                }
            }
            cout<<"Jump to "<<*it<<endl;
            ct++;
        }
        return ct;
    }
    void disp(vector<int>& nums)
    {
        for(int a:nums)
        {
            cout<<a<<" ";
        }
        cout<<endl;
    }
};
int main()
{
    Solution s1;
    vector<int>arr={3,5,1,2,3,2,1,3,2};
    s1.disp(arr);
    cout<<s1.jump(arr);
}
