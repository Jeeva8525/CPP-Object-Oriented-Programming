/* 
Leetcode problem - 1493
*/
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
    int longestSubarray(vector<int> &nums)
    {
        int leftCount = 0, rightCount = 0, res = 0, zeroAppeared = 0;
        for (int x : nums)
        {
            if (x)
            {
                leftCount++;
                if (zeroAppeared == 1)
                    rightCount++;
            }
            else if(zeroAppeared == 1)
            {
                if (leftCount > res)
                res = leftCount;
                leftCount = rightCount;
                rightCount = 0;
                zeroAppeared = 1;
            }
            else
            {
                zeroAppeared = 1;
            }
        }
        if (leftCount > res)
            res = leftCount;
        return zeroAppeared != 0 ? res : res - 1;
    }
};
int main()
{
    Solution s;
    vector<int> vec = {1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1};
    cout << s.longestSubarray(vec);
}