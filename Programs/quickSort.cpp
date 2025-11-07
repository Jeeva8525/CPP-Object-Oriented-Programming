#include <vector>
#include <iostream>
using namespace std;
typedef vector<int> vInt; 
int median3(vInt &arr,int l,int r)
{
    int med = (l+r)/2;
    if(arr[med] > arr[l]) swap(arr[med],arr[l]);
    if(arr[med] > arr[r]) swap(arr[med],arr[r]);
    if(arr[l] > arr[r]) swap(arr[l],arr[r]);
    return med;
}
void quickSort(vInt &vec,int left,int right)
{
    if(left > right )return;
    
    swap(vec[median3(vec,left,right)],vec[left]);
    int pivot = vec[left];
    int x = left+1,y = right;
    while(x<=y)
    {
        while(vec[x] <= pivot) x++;
        while(vec[y] > pivot) y--;
        if(x<y)
        {
            swap(vec[x++],vec[y--]);
        }
    }
    swap(vec[y],vec[left]);
    quickSort(vec,left,y-1);
    quickSort(vec,y+1,right);
    
}
int main()
{
    vInt v = { 9,8,7,6,5,4,3,2,1};
    quickSort(v,0,v.size()-1);
    for(int x : v)
    {
        cout<<x<<" ";
    }
}