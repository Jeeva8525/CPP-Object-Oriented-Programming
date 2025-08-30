/* 
implementation of insertion and deletion function in a binary heap data structure
*/

#include <iostream>
#define size 100 // can store 99 elts as 0th index can't be used
using namespace std;
class binHeap
{
public:
    int arr[size];
    int len;
    binHeap()
    {
        len = 0;
    }
    void printTree()
    {
        cout << "The elements in the tree are" << endl;
        for (int x = 1; x <= len; x++)
        {
            cout << arr[x] << " ";
        }
        cout << endl;
        for (int x = 1; x <= len; x++)
        {
            cout << "| ";
        }
        cout << endl;
        for (int x = 1; x <= len; x++)
        {
            cout << x << " ";
        }
        cout << " -- index" << endl;
    }
    void insert(int val)
    {
        int x;
        if (len >= size - 1)
        {
            cout << "Tree is full" << endl;
            return;
        }
        for (x = ++len; (x / 2) > 0 && val < arr[x / 2]; x /= 2)
        {
            arr[x] = arr[x / 2];
        }
        arr[x] = val;
    }
    void deleteMin()
    {
        if(len<1)
        {
            cout<<"No elt to delete";
            return;
        }
        int minElt = arr[1];
        int lastElt = arr[len--];
        int child,x;
        for (x = 1; x * 2 <= len; x = child)
        {
            child = 2 * x;
            if(child != len && arr[child]>arr[child+1])
            child++;
            if(lastElt>arr[child])
            {
                cout<<"The child is "<<child<<endl;
                arr[x] = arr[child];
            }
            else
                break;
        }
        arr[x] = lastElt;
    }
};
int main()
{
    binHeap h1;
    cout << "1 : add an element\n2 : delete an element\n3 : exit" << endl;
    int ch, val;
    do
    {
        cout << "Choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "Enter the value: ";
            cin >> val;
            h1.insert(val);
            h1.printTree();
            break;
        case 2:
            h1.deleteMin();
            h1.printTree();
            break;
        default:
            ch = 0;
        }
    } while (ch != 0);
}