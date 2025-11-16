/* 
Jump game - 1 (LeetCode Problem - 55)
*/
#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    bool canJump(vector<int>& nums) {
        if(nums.size()==1)
            return 1;
        if(nums.size()==2)
        {
            if(nums[0]==0)
                return 0;
            else
                return 1;
        }


        int max=nums[1]+1,max_index=1;
        int y=nums[0],y_index=0;
        for(int x=2;x<nums.size();x++)
        {

            if((max<=nums[x]+x) && x<=y+y_index)
            {
                max=nums[x]+x;
                max_index=x;
            }

            if(x>y+y_index)
            {
                //cout<<"\nMax is "<<max<<"\nmax_index is "<<max_index<<endl; //1 1 0 1
                if(max==(x-1)+0)
                {
                    return 0;
                }
                x=max_index+1;
                y=nums[max_index];
                y_index=max_index;
                max=nums[x]+x;
                max_index=x;;
            }
        }
        return 1;

    }
};
int main()
{
    Solution S;
    vector<int>arr={1,1,0,1};
    cout<<S.canJump(arr);
}
