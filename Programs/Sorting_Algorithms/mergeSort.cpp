#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> vInt;
vInt mergeSort(vInt arr)
{
    if(arr.size() == 0 || arr.size() == 1)
    {
        return arr;
    }
    vInt a = mergeSort(vInt(arr.begin(),arr.begin()+arr.size()/2));
    vInt b = mergeSort(vInt(arr.begin()+arr.size()/2,arr.end()));
    int i=0,j=0;
    vInt res;
    while(i<a.size() || j<b.size())
    {
        if(i<a.size() && j<b.size())
        {
            if(a[i] < b[j])
            {
                res.push_back(a[i++]);
            }
            else
            {
                res.push_back(b[j++]);
            }
        }
        else if(i<a.size())
        {
            res.push_back(a[i++]);
        }
        else
        {
            res.push_back(b[j++]);
        }
    }
    return res;
}
int main()
{
    vInt a = { 8, 7, 6, 5, 9, 4, 3, 2, 1};
    a = mergeSort(a);
    for(int x : a)
    {
        cout<<x<<" ";
    }
}