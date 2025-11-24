#include <iostream>
using namespace std;
#include <vector>

class Solution {
public:
    int removeElement(vector<int> &nums, int val)
    {
        if(nums.size() == 0) return 0;
        int backPtr = nums.size() - 1;
        int frontPtr = 0;
        while (frontPtr <= backPtr)
        {
            while(frontPtr <= backPtr && nums[frontPtr]!=val)
                frontPtr++;
            while(backPtr >= frontPtr && nums[backPtr]==val)
                backPtr--;
            if(frontPtr < backPtr)
                swap(nums[frontPtr++],nums[backPtr--]);
        }
        cout<<(frontPtr==backPtr?frontPtr+1:frontPtr)<<endl;
        return frontPtr==backPtr?frontPtr+1:frontPtr;
    }
};
int main()
{
    // vector<int> vec = {3,2,2,3};
    vector<int> vec = {1};
    Solution s;
    s.removeElement(vec,1);
    for(int x : vec) cout<<x<<" "; cout<<endl;
}