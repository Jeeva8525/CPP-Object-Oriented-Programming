/* 
Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas. The guards have gone and will come back in h hours.

Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some pile of bananas and eats k bananas from that pile. If the pile has less than k bananas, she eats all of them instead and will not eat any more bananas during this hour.

Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.

Return the minimum integer k such that she can eat all the bananas within h hours.
Leetcode problem - 875
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int min = 1;
        int max;
        long long sum;
        auto it = max_element(piles.begin(),piles.end());
        max = *it;
        int searchVal,res;
        while(min<=max)
        {
            searchVal = (min + max)/2;
            sum = 0;
            for( int x : piles)
                sum+=(x-1)/searchVal+1;
            if(sum <= h)
            {
                max = searchVal-1;
                res = searchVal;
            }
            else
                min = searchVal+1;
        }
        return res;
    }
};
int main()
{
    Solution s;
    vector<int>vec = {3,6,7,11};
    cout<<s.minEatingSpeed(vec,8);
}