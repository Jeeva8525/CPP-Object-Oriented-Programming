#include <iostream>
#include <vector>
#include <queue>
#define inf INT_MAX
using namespace std;
class Graph
{
    int nv;                              // no. of vertices
    vector<vector<pair<int, int>>> list; // <value,weight>
    vector<bool> visited;
    bool isDir;

public:
    Graph(int n, bool dir = false)
    {
        nv = n;
        list.resize(n);
        visited.resize(n, false);
        isDir = dir;
    }

    void addEdge(int u, int v, int weight)
    {

        list[u].push_back({v, weight});
        if (!isDir)
        {
            list[v].push_back({u, weight});
        }
        // cout<<"Added "<<u<<" to "<<v<<" successfully"<<endl;
    }
    void printGraph()
    {
        for (int x = 1; x < nv; x++)   // where, nv = no of vertices + 1
        {
            cout << x << " -> ";
            for (pair y : list[x])
            {
                cout << y.first << "(" << y.second << ") , ";   //a(b) means x is linked to 'a' with weight 'b'
            }
            cout << endl;
        }
        cout << endl;
    }

    void BFS(int startPos = 1)
    {
        cout << "BFS : ";
        queue<int> q;
        fill(visited.begin(), visited.end(), false);

        q.push(startPos);
        visited[startPos] = true;
        cout << startPos << " ";
        while (!q.empty())
        {
            int temp = q.front(); q.pop();
            for (pair x : list[temp])
            {
                if (!visited[x.first])
                {
                    q.push(x.first);
                    cout << x.first << " ";
                    visited[x.first] = true;
                }
            }
        }
        cout << endl;
    }

    void DFS_func(int startPos)
    {
        visited[startPos] = true;
        for (pair x : list[startPos])
        {
            if (!visited[x.first])
            {
                cout << x.first << " ";
                visited[x.first] = true;
                DFS_func(x.first);
            }
        }
    }
    void DFS(int startPos = 1)
    {
        cout << "DFS : ";
        cout << startPos << " ";
        fill(visited.begin(), visited.end(), false);
        DFS_func(startPos);
        cout << endl;
    }
    void MST_Prim(int startPos)
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        vector<int> dist(nv, inf);
        vector<int> parent(nv, -1);
        vector<bool> known(nv, 0);

        dist[startPos] = 0;
        // known[startPos] = 1;
        pq.push({0, startPos});
        while (!pq.empty())
        {
            pair<int, int> temp = pq.top(); pq.pop();

            if (known[temp.second])
                continue;
            known[temp.second] = true;

            for (pair<int, int> x : list[temp.second])
            {
                // cout<<"TEST1"<<endl;
                if (!known[x.first] && x.second < dist[x.first])
                {
                    // cout<<"TEST2"<<endl;
                    dist[x.first] = x.second;
                    parent[x.first] = temp.second;
                    pq.push({dist[x.first], x.first});
                }
            }
        }

        cout << "Edges in MST \n";
        int sum = 0;
        for (int x = 1; x < parent.size(); x++)
        {
            cout << parent[x] << "->" << x << " Weight - " << dist[x] << endl;
            sum += dist[x];
        }
        cout << "Total weight : " << sum << endl;
    }
};
int main()
{
    Graph g1(7 + 1, false);
    g1.addEdge(3, 1, 4);
    g1.addEdge(3, 4, 2);
    g1.addEdge(3, 6, 5);
    g1.addEdge(1, 4, 1);
    g1.addEdge(1, 2, 2);
    g1.addEdge(6, 7, 1);
    g1.addEdge(4, 2, 3);
    g1.addEdge(4, 7, 4);
    g1.addEdge(4, 5, 7);
    g1.addEdge(4, 6, 6);
    g1.addEdge(2, 5, 10);
    g1.addEdge(7, 5, 6);
    g1.printGraph();
    cout << "\n\n";
    g1.BFS(1);
    g1.DFS(1);

    cout << " -------------------------- " << endl;
    g1.MST_Prim(1);
}
