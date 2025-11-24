#include <iostream>
using namespace std;
#include <vector>
class Solution
{
public:
    int searchInsert(vector<int> &nums, int target)
    {
        int low = 0, high = nums.size() - 1;
        int mid;
        while (low <= high)
        {
            mid = low + (high - low) / 2;
            if(nums[mid] == target)
                return mid;
            if(target < nums[mid])
                high = mid-1;
            if(target > nums[mid])
                low = mid+1;
        }
        return low;
    }
};
int main()
{
    vector<int> vec = {3, 4, 7, 9};
    Solution s;
    cout<<s.searchInsert(vec,4);
    cout<<s.searchInsert(vec,5);
    cout<<s.searchInsert(vec,6);
    cout<<s.searchInsert(vec,7);
    cout<<s.searchInsert(vec,8);
}