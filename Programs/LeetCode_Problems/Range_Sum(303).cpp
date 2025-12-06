#include<iostream>
using namespace std;
#include <vector>

class NumArray {
    vector<int> vec;
public:
    NumArray(vector<int>& nums) {
        vec.resize(nums.size()) ;
        vec[0] = nums[0];
        for(int x=1;x<nums.size();x++)
        {
            vec[x] = vec[x-1] + nums[x];
        }
    }
    
    int sumRange(int left, int right) {
        int low = left == 0 ? 0 : vec[left-1];
        return vec[right]-low;
    }
};

int main()
{
    vector<int> vec = {-2, 0, 3, -5, 2, -1};
    NumArray na(vec);
    cout<<na.sumRange(3,4)<<endl;
    cout<<na.sumRange(2,5)<<endl;
    cout<<na.sumRange(0,1)<<endl;

}