#include<iostream>
#include<vector>
using namespace std;
typedef vector<int> vInt;
/* int findPivot(vInt &vec,int l,int r)
{
    int idx = l; 
    swap(vec[idx],vec[l]); 
    return vec[l];
} */
int findPivot(vInt &vec,int l,int r)
{
    int mid = (l+r)/2; 
    if(vec[l]>vec[r]) swap(vec[l],vec[r]);
    if(vec[mid]>vec[r]) swap(vec[mid],vec[r]);
    if(vec[l]>vec[mid]) swap(vec[l],vec[mid]);

    
    swap(vec[mid],vec[l]); 
    return vec[l];
}
int quickS(vInt &vec,int left,int right)
{
  
    int pivot = findPivot(vec,left,right);  
    int x = left+1;
    int y = right;

    while(x<=y)
    {
        while(x<=right && vec.at(x)<=pivot) x++;
        while(y>=left && vec.at(y)>pivot) y--;
        if(x<y)
            swap(vec[x++],vec[y--]);
    }
    swap(vec[left],vec[y]);
    return y;
}
void quickSort(vInt &vec,int left,int right)
{
    if(left>=right) return;
    int p = quickS(vec,left,right);
    quickSort(vec,left,p-1);
    quickSort(vec,p+1,right);
}
int main()
{
    vInt vec = { 7,6,5,4,3,2,1};
    cout<<"Before Sorting"<<endl;
    for(int x:vec)
    {
        cout<<x<<" ";    
    }
    cout<<endl;
    quickSort(vec,0,vec.size()-1);
    cout<<"After Sorting"<<endl;
    for(int x:vec)
    {
        cout<<x<<" ";    
    }
    cout<<endl;
}