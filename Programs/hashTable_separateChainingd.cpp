#include <iostream>
#include <vector>
#include <list>
using namespace std;
typedef vector<int> vint;
class HashTable
{
    vector<list<int>> table;
    int size;
    public:
    HashTable(int size)
    {
        this->size = size;
        table.resize(size);
        // fill(table.begin(),table.end(),temp);
    }
    int hashFunction(int key)
    {
        return key%size;
    }

   //quadratic probing
    void insertKey(int value)
    {
        table[hashFunction(value)].push_back(value);
    }
    void display()
    {
        for(int x = 0 ; x<table.size() ; x++)
        {
            cout<<x<<" : ";
            for(int y : table[x])
            {
                cout<<y<<" ";
            }
            cout<<endl;
        }
    }
};
int main()
{
    HashTable h1(10);
    h1.insertKey(4);
    h1.insertKey(6);
    h1.insertKey(8);
    h1.insertKey(14);
    h1.insertKey(24);
    h1.display();
}