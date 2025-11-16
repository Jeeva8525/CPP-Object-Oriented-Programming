#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
typedef vector<int> vint;
class HashTable
{
    vint table;
    int size;
    public:
    HashTable(int size)
    {
        this->size = size;
        table.resize(size,-1);
    }
    int hashFunction(int key)
    {
        return key%size;
    }
    /* void insertKey(int value)
    {
        int org_index = hashFunction(value);
        int index = org_index;
        while(table[index] != -1)
        {
            index =(index+1)%size;
            if(index == org_index)
            {
                cout<<"The table is full | Can't insert element "<<endl;
                return;
            }
        }
        table[index] = value;
    } */


   //quadratic probing
    /* void insertKey(int value)
    {
        int org_index = hashFunction(value);
        int index = org_index;
        int x = 0;
        while(table[index] != -1)
        {

            x++;
            if(x == size)
            {
                cout<<"The table is full | Can't insert element "<<endl;
                return;
            }
            index = (org_index+x*x)%size;
            cout<<"Value of x is "<<x<<endl;
        }
        table[index] = value;
    } */
    int hash2(int key)
    {
        return 1;
    }
    void insertKey(int value)
    {
        int h1 = hashFunction(value);
        int h2 = hash2(value);
        int x = 0 ;
        while(x<size)
        {
            int index = (h1 + x * h2)%size;
            if(table[index] == -1 || table[index] == -2)
            {
                table[index] = value;
                return;
            }
            x++;
        }
        cout<<"No empty space to fit in table"<<endl;
    }
    void display()
    {
        int d=0;
        for(int x: table) cout<<setw(5)<<(d++)<<" : "<<setw(5)<<x<<endl;
    }

    int nextPrime(int value)
    {
        bool isPrime;
        for(int x = value ; x < 1000 + value ; x++)
        {
            isPrime = true;
            for(int y=2 ;y < x/2 ; y++)
            {
                if(x%y == 0)
                {
                    isPrime =false;
                    break;
                }
            }
            if(isPrime)
                return x;
        }
        cout<<"no prime numbers found within next 1000 numbers return double the original value"<<endl;
        return 2 * value; // if no prime numbers found within next 1000 numbers return double the original value
    }
    void rehash()
    {
        int prevTableSize = size;
        vint oldTable(table.begin(),table.end());
        size = nextPrime(2 * prevTableSize);
        table.assign(size,-1);
        // fill(table.begin(),table.end(),-1);
        for(int x : oldTable)
        {
            if(x != -1 && x!= -2)
                insertKey(x);
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
    cout<<"---------REHASHING-----------"<<endl;
    h1.rehash();
    h1.display();
}