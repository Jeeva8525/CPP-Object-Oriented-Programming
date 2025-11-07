#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;
class Solution
{
public:
    string sortVowels(string s)
    {
        string str = "AEIOUaeiou";
        priority_queue<int, vector<int>, greater<int>> pq;
        for (char x : s)
        {
            if (str.find(x) != string::npos)
            {
                pq.push(x);
            }
        }
        for (int x = 0; x < s.length(); x++)
        {
            if (str.find(s[x]) != string::npos)
            {
                s[x] = pq.top();
                pq.pop();
            }
        }
        return s;
    }
};
int main()
{
    Solution s;
    cout << "Sorted : " << s.sortVowels("OEIoiOEAUEaiIAIAeaAiOIuuOUeUUoEAEEEuIIioeIEaEoEUiaUuIAuiaeaoIaeoiEOOOIIIaiaiOeooOuaaiaAOAIOOOiAaeiUA") << endl;
}