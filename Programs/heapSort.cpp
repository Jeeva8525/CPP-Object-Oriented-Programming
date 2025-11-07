#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> vInt;
void percolate_down(vInt &vec, int val, int idx,int size)
{
    int lastIdx =size-1;
    // cout<<"Size is "<<lastIdx<<endl;
    int child, x;
    for (x = idx; 2 * x <= lastIdx; x = child)
    {
        child = 2 * x;
        // cout<<"Child -> "<<child<<endl;
        if (child != lastIdx && vec[child] < vec[child + 1])
        {
            child++;
            // cout<<" inc exec ---"<<endl;
        }
        if (val < vec[child])
            vec[x] = vec[child];
        else
            break;
    }
    vec[x] = val;
}
void max_heapify(vInt &vec,int size)
{
    int lastIdx = size-1;
    int n = lastIdx/2;
    for (int x = n; x > 0; x--)
    {
        percolate_down(vec,vec[x],x,vec.size());
    }
}
void heap_sort(vInt &vec)
{
    max_heapify(vec,vec.size());
    for(int x=vec.size()-1;x>0;x--)
    {
        swap(vec[1],vec[x]);
        percolate_down(vec,vec[1],1,x);
    }
}
int main()
{
    vInt vec;
    int n,val;
    cout<<"Enter the no. of elements: ";
    cin>>n;
    vec.push_back(0);
    for(int x=0;x<n;x++)
    {
        cout<<" Element - "<<x+1<<" : ";
        cin>>val;
        vec.push_back(val);
    }
    for(int x=1;x<vec.size();x++)
    {
        cout<<vec[x]<<" ";
    }
    cout<<endl;
    heap_sort(vec);
    for(int x=1;x<vec.size();x++)
    {
        cout<<vec[x]<<" ";
    }
    cout<<endl;
}
