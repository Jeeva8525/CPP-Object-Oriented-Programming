/* 
Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Every close bracket has a corresponding open bracket of the same type.
*/
#include <iostream>
#include <stack>
using namespace std;
int isValidParanthesis(string str)
{
    stack<char>s;
    s.push('@'); //temporary character so that s.top() wont crash
    for(int x=0;str[x];x++)
    {
        if(str[x]==')')
        {
            if(s.top()!='(')
                return 0;
            s.pop();
        }
        else if(str[x]==']')
        {
            if(s.top()!='[')
                return 0;
            s.pop();
        }
        else if(str[x]=='}')
        {
            if(s.top()!='{')
                return 0;
            s.pop();
        }
        else
        {
            s.push(str[x]);
        }
    }

    s.pop(); //to pop '@'
    if(s.empty())
        return 1;
    else
        return 0;
}

int main()
{
    string str = "[()]";
    cout<<"Is the parantheses valid: "<<isValidParanthesis(str);
}
