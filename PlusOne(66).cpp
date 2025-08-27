/* 
You are given a large integer represented as an integer array digits, where each digits[i] is the ith digit of the integer. The digits are ordered from most significant to least significant in left-to-right order. The large integer does not contain any leading 0's.

Increment the large integer by one and return the resulting array of digits.
*/
#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        for(int x=digits.size()-1;x>=0;x--){
            if(digits[x]==9 && x==0){
                digits[0]=0;
                digits.insert(digits.begin(),1);
            }
            if(digits[x]!=9){
                digits[x]+=1;
                break;
            }
            digits[x]=0;
        }
        return digits;
    }
};
int main(){
    Solution s1;
    vector<int>nums={1,2,3};
    cout<<"The incremented array is "<<endl;
    s1.plusOne(nums);
    for(int x=0;x<nums.size();x++){
        cout<<nums[x]<<" ";
    }
}