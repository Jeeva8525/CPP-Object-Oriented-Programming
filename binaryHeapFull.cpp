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
        if (len >= size - 1)
        {
            cout << "Tree is full" << endl;
            return;
        }
        percolateUp(++len, val);
    }
    int deleteMin()
    {
        if (len < 1)
        {
            cout << "No elt to delete";
            return -1;
        }
        int minElt = arr[1];
        int lastElt = arr[len--];
        percolateDown(1, lastElt);
        return minElt;
    }
    void percolateUp(int idx, int val)
    {
        int x;
        for (x = idx; x > 1 && arr[x / 2] > val; x = x / 2)
        {
            arr[x] = arr[x / 2];
        }
        arr[x] = val;
    }
    void percolateDown(int idx, int val)
    {
        int x, child;
        for (x = idx; (2 * x) <= len; x = child)
        {
            child = 2 * x;
            if (child != len && arr[child + 1] < arr[child])
            {
                child++;
            }
            if (arr[child] < val)
            {
                arr[x] = arr[child];
            }
            else
                break;
        }
        arr[x] = val;
    }
    void increaseKey(int idx, int key)
    {
        if (arr[idx] > key)
        {
            cout << "Key value must be greater than the original value" << endl;
            return;
        }
        percolateDown(idx, key);
    }
    void decreaseKey(int idx, int key)
    {
        if (arr[idx] < key)
        {
            cout << "Key value must be lesser than the original value" << endl;
            return;
        }
        percolateUp(idx, key);
    }
    void deleteArbitraryElt(int val)
    {
        for (int x = 1; x <= len; x++)
        {
            if (val == arr[x])
            {
                int lastElt = arr[len--];
                percolateDown(x, lastElt);
                break;
            }
        }
        cout << "No such element" << endl;
    }
    void findKthMin(int n)
    {
        int temp = len;
        int *arr2 = new int[len + 1];
        for (int x = 1; x <= len; x++)
        {
            arr2[x] = arr[x];
        }
        for(int x = 1 ; x<n;x++)
        {
            deleteMin();
        }
        cout<<"The "<<n<<" - minimum element in the heap is "<<arr[1]<<endl;
        len = temp;
        for (int x = 1; x <= len; x++)
        {
            arr[x] = arr2[x];
        }
    }
};
int main()
{
    binHeap h1;
    cout << "1 : add an element\n2 : delete min element\n3 : delete an element\n4 : increase key\n5 : decrease key\n6 : Find the kth minimum elt in the heap\n7 : exit" << endl;
    int ch, val, index;
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
            break;
        case 2:
            h1.deleteMin();
            break;
        case 3:
            cout << "Enter the element to be deleted: ";
            cin >> val;
            h1.deleteArbitraryElt(val);
            break;
        case 4:
            cout << "Enter the index : ";
            cin >> index;
            cout << "Enter value : ";
            cin >> val;
            h1.increaseKey(index, val);
            break;
        case 5:
            cout << "Enter the index : ";
            cin >> index;
            cout << "Enter value : ";
            cin >> val;
            h1.decreaseKey(index, val);
            break;
        case 6:
            cout<<"Enter k : ";
            cin>>val;
            h1.findKthMin(val);
            break;
        default:
            ch = 0;
        }
        h1.printTree();
    } while (ch != 0);
}