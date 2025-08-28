/* 
Given a string s consisting of words and spaces, return the length of the last word in the string.

A word is a maximal substring consisting of non-space characters only.

LeetCode Problem - 58
*/
#include <iostream>
using namespace std;

class Solution {
public:
    int lengthOfLastWord(string s) {
        int marker=0;
        int len=0;
        for(int x=s.length()-1;x>=0;x--){
            if(s[x]==' ' && marker){
                break;
            }
            if(s[x]!=' '){
                len+=1;
                marker=1;
            }
            
        }
        return len;
    }
};
int main(){
    Solution s1;
    string str="The last word is also in the words";
    cout<<"The length of the last word is "<<s1.lengthOfLastWord(str);
}