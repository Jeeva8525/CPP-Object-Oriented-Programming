#include <iostream>
using namespace std;
#include <vector>
class Solution {
public:
    int maxArea(vector<int>& height) {
        int maxArea = 0;
        int left = 0;
        int right = height.size()-1;

        while(left<right)
        {
            int curArea = min(height[left],height[right])*(right-left);
            maxArea = maxArea>=curArea?maxArea:curArea;
            if(height[left]>height[right]) 
                right--;
            else    
                left++;
        }
        return maxArea;
    }
};
int main()
{
    Solution s;
    vector<int> vec = {1,8,6,2,5,4,8,3,7};
    cout<<s.maxArea(vec);

}