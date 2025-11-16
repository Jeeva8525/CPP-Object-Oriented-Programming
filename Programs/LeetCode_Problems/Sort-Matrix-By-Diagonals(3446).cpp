/* 
You are given an n x n square matrix of integers grid. Return the matrix such that:

The diagonals in the bottom-left triangle (including the middle diagonal) are sorted in non-increasing order.
The diagonals in the top-right triangle are sorted in non-decreasing order.

LeetCode problem - 3446
*/

#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;
class Solution
{
public:
    void print(vector<vector<int>> &grid)
    {
        cout<<"The elts are"<<endl;
        for (int x = 0; x < grid.size(); x++)
        {
            for (int y = 0; y < grid[0].size(); y++)
            {
                cout << grid[x][y] << " ";
            }
            cout << endl;
        }
    }
    vector<vector<int>> sortMatrix(vector<vector<int>> &grid)
    {
        priority_queue<int> pqDesc;
        priority_queue<int, vector<int>, greater<int>> pqAsc;
        // Lower diagonal - non increasing order ... including the main diagonal
        for (int x = -grid.size() + 1; x <= 0; x++)
        {
            for (int y = 0; (y - x) < grid[0].size(); y++)
            {
                pqDesc.push(grid[y - x][y]);
            }
            for (int y = 0; (y - x) < grid[0].size(); y++)
            {
                grid[y - x][y] = pqDesc.top();
                pqDesc.pop();
            }
        }
        cout << endl;
        // Upper diagonal - non decreasing order
        for (int y = 1; y < grid.size(); y++)
        {
            for (int x = 0; (x + y) < grid[0].size(); x++)
            {
                pqAsc.push(grid[x][x+y]);
            }
            for (int x = 0; (x + y) < grid[0].size(); x++)
            {
                grid[x][x+y] = pqAsc.top();
                pqAsc.pop();
            }
        }
        return grid;
    }
};
int main()
{
    Solution s;
    // vector<vector<int>> arr = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    vector<vector<int>> arr = {{1,7,3},{9,8,2},{4,5,6}};
    cout<<"Elements before sorting"<<endl;
    s.print(arr);
    s.sortMatrix(arr);
    cout<<"Elements after sorting"<<endl;
    s.print(arr);
}