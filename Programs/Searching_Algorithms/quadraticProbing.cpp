#include <iostream>
using namespace std;
class HashTable
{
private:
    int* arr;
    int size;
public:
    HashTable(int n)
    {
        size = n;
        arr = new int[n];
        fill(arr,arr+n,-1);
    }
    int hash(int x)
    {
        return x % size;
    }
    void insert(int elt)
    {
        int idx = hash(elt);
        int x = 0;
        while(arr[(idx+ (x*x))%size]!=-1)
        {
            x++;
            if(x == size)
            {
                cout<<"Table is full"<<endl;
                return;
            }
        }
        arr[(idx + (x*x))%size] = elt;
    }
    void display()
    {
        for(int x=0;x<size;x++)
        {
            cout<<arr[x]<<" ";
        }
        cout<<endl;
    }
};
int main()
{
    HashTable h1(5);
    h1.insert(4);
    h1.insert(3);
    h1.insert(7);
    h1.insert(9);
    h1.display();
}