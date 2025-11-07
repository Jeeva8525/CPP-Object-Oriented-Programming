#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Unity
{
    vector<int>rank;
    vector<int>parent;
public:
    Unity(int n)
    {
        rank.resize(n,0);
        parent.resize(n);
        for(int x=0;x<parent.size();x++)
        {
            parent[x] = x;
        }
    }
    int findParent(int x)
    {
        if(parent[x]!=x)
        {
            parent[x] = findParent(parent[x]);
        }
        return parent[x];
    }
    bool unite(int u,int v)
    {
        int ru=findParent(u);
        int rv=findParent(v);
        if(ru == rv)
        {
            return false;
        }

        if(rank[ru] > rank[rv])
        {
            parent[rv] = parent[ru];
        }
        else if(rank[ru] < rank[rv])
        {
            parent[ru] = rv;
        }
        else
        {
            parent[rv] = ru;
            rank[ru]++;
        }
        return true;
    }
};
struct Edge{
    int u,v,w;
};
class Graph
{
    // vector<vector<pair<int,int>>>list;
    int nv;
    vector<Edge>edges;
    bool isDir;
public:
    Graph(int n,int dir = false)
    {
        nv = n;
        isDir = dir;
        edges.resize(n);
    }
    void addEdge(int u,int v,int w)
    {
       edges.push_back({u,v,w});
    }

    void kruskal()
    {
        Unity u(nv);
        vector<Edge>result;
        sort(edges.begin(),edges.end(),[](Edge a,Edge b){
            return a.w < b.w;
        });
        for(Edge e : edges)
        {
            if(u.unite(e.u,e.v))
            {
                result.push_back(e);
            }
        }

        cout<<" ----------------- "<<endl;
        for(Edge e : result)
        {
            cout<<e.u<<" -> "<<e.v<<endl;
        }
    }
};
int main()
{
    Graph g1(7);
    g1.addEdge(0,1,3);
    g1.addEdge(0,2,6);
    g1.addEdge(0,3,6);
    g1.addEdge(1,2,3);
    g1.addEdge(1,3,3);
    g1.addEdge(2,3,2);

    g1.kruskal();
}