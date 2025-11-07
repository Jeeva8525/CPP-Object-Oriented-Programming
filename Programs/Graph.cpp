#include <iostream>
#include <vector>
#include <queue>
#define inf INT_MAX
using namespace std;
class Graph
{
    int nv; //no. of vertices
    vector<vector<int>> list;
    vector<bool>visited;
    bool isDir;
    
public:
    Graph(int n,bool dir)
    {
        nv = n;
        list.resize(n);
        visited.resize(n,false);
        isDir = dir;
    }

    void addEdge(int u,int v)
    {
        list[u].push_back(v);
        if(!isDir)
        {
            list[v].push_back(u);
        }
        // cout<<"Added "<<u<<" to "<<v<<" successfully"<<endl;
    }
    void printGraph()
    {
        for(int x=0;x<nv;x++)
        {
            cout<<x<<" -> ";
            for(int y:list[x])
            {
                cout<<y<<" , ";
            }
            cout<<endl;
        }
        cout<<endl;
    }

    void BFS(int startPos)
    {
        queue<int>q;
        fill(visited.begin(),visited.end(),false);

        q.push(startPos);
        visited[startPos] = true;
        cout<<startPos<<" ";
        while(!q.empty())
        {
            int temp = q.front() ; q.pop() ; 
            for(int x:list[temp])
            {
                if(!visited[x])
                {
                    q.push(x);
                    cout<<x<<" ";
                    visited[x] = true;
                }
            }
        }
    }

    void DFS_func(int startPos)
    {
        visited[startPos] = true ;
        for(int x:list[startPos])
        {
            if(!visited[x])
            {
                cout<<x<<" ";
                visited[x] = true;
                DFS_func(x);
            }
        }
    }
    void DFS(int startPos)
    {
        cout<<startPos<<" ";
        fill(visited.begin(),visited.end(),false);
        DFS_func(startPos);
    }
};
int main()
{
    Graph g1(7+1,false);
    g1.addEdge(3,1);
    g1.addEdge(3,4);
    g1.addEdge(3,6);
    g1.addEdge(1,4);
    g1.addEdge(1,2);
    g1.addEdge(6,7);
    g1.addEdge(4,2);
    g1.addEdge(4,7);
    g1.addEdge(4,5);
    g1.addEdge(4,6);
    g1.addEdge(2,5);
    g1.addEdge(7,5);
    // g1.printGraph();
    cout<<"\n\n";
    // g1.BFS(1);
    g1.DFS(1);
}