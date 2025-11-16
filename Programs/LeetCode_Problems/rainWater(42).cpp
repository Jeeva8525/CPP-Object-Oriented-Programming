/* 
Given n non-negative integers representing an elevation map where the width of each bar is 1,
compute how much water it can trap after raining.

LeetCode problem - 42
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
public:
    int trap(vector<int> &height)
    {
        int sum = 0, dist = 0,decreaser = 0;
        int prev = height[0];
        int prevIndex = 0;
        for (int x = 1; x < height.size(); x++)
        {
            dist++;
            if (height[x] >= prev)
            {
                sum += prev * (dist - 1) - decreaser;
                decreaser = 0; 
                prev = height[x];
                prevIndex = x;
                dist = 0;
            }
            else if(x!=height.size()-1 )
            {
                decreaser += height[x];
            }
            else
            {
                vector<int>temp;
                temp.assign(height.rbegin(),height.rbegin()+(height.size()-prevIndex));
                sum+=trap(temp);
            }
        }
        return sum;
    }
};
int main()
{
    vector<int> arr = {4,2,3};
    Solution s;
    cout << s.trap(arr)<<endl;
}