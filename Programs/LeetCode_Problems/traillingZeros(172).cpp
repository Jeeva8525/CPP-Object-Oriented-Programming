/* 
LeetCode Problem - 172

return the number of trailing zeros in the n's factorial
*/
#include <iostream>
using namespace std;
class Solution
{
    public:
    int trialingZeroes(int n)
    {
        int sum;
        while(n>4)
        {
            n/=5;
            sum+=n;
        }
        return sum;
    }
};
int main()
{
    Solution s;
    int n;
    cout<<"Enter the numebr: ";
    cin>>n;
    cout<<s.trialingZeroes(n);
}