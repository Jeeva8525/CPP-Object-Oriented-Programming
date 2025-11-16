//Sorting algos
#include <vector>
#include <iostream>
#include <algorithm> //for Counting sort
using namespace std;
typedef vector<int> vint;
void insertionSort(vint &vec)
{
    for(int x=1;x<vec.size();x++)
    {
        int y=x-1;
        int elt = vec[x]; //
        while(y>=0 && vec[y]>elt)
        {
            vec[y+1] = vec[y];
            y--;
        }
        vec[y+1] = elt; 
    }
} 


//Heap Sort
void percolate_down(vint &vec,int index,int value,int maxIndex)
{
    int x;
    int child;
    int elt = vec[index];
    for(x = index ; 2 * x <= maxIndex ; x = child)
    {
        child = 2*x;
        if(child != maxIndex && vec[child+1] > vec[child])
            child++;
        if(vec[child] > elt)
            vec[x] = vec[child];
        else
            break;
    }
    vec[x] = elt;
}
void max_heapify(vint &vec)
{
    for(int x = vec.size()/2 ; x >= 0 ; x--)
    {
        percolate_down(vec,x,vec[x],vec.size()-1);
    }
}
void heapSort(vint &vec)
{
    max_heapify(vec);
    for(int len = vec.size()-1;len>0;len--)
    {
        swap(vec[0],vec[len]);
        percolate_down(vec,0,vec[0],len-1);
    }
}


//merge sort
void merger(vint &vec,int left,int mid,int right)
{
    vint LA(vec.begin()+left,vec.begin()+mid+1);
    vint RA(vec.begin()+mid+1,vec.begin()+right+1);

    int l=0,r=0,d=left;
    while(l < LA.size() && r < RA.size())
    {
        if(LA[l] < RA[r])
            vec[d++] = LA[l++];
        else
            vec[d++] = RA[r++];
    }
    while(l < LA.size())
        vec[d++] = LA[l++];
    while(r < RA.size())
        vec[d++] = RA[r++];
}
void mergeCaller(vint &vec,int left,int right)
{
    if(left < right)
    {
        int mid = left + (right - left)/2;
        mergeCaller(vec,left,mid);
        mergeCaller(vec,mid+1,right);
        merger(vec,left,mid,right);
    }
}
void mergeSort(vint &vec)
{
    mergeCaller(vec,0,vec.size()-1);
}

//quick Sort
void setPivotAtLeft(vint &vec,int left,int right)
{
    //median3
    int mid = left + (right-left)/2;
    if(vec[left] > vec[mid]) swap(vec[mid],vec[left]);
    if(vec[left] > vec[right]) swap(vec[left],vec[right]);
    if(vec[mid] > vec[right]) swap(vec[mid],vec[right]);
    int index = mid;
    swap(vec[left],vec[index]);
}
int partition(vint &vec,int left,int right)
{
    setPivotAtLeft(vec,left,right);
    int pivot = left;
    int lptr = left+1 , rptr = right;
    while(lptr <= rptr)
    {
        while(vec[lptr] <= vec[pivot]) lptr++;
        while(vec[rptr] > vec[pivot]) rptr--;
        if(lptr < rptr)
        {
            swap(vec[lptr],vec[rptr]);
            lptr++;
            rptr--;
        }
    }
    swap(vec[left],vec[rptr]);
    return rptr;
}
void quickSortCaller(vint &vec,int left,int right)
{
    if(left < right)
    {
        int pivot = partition(vec,left,right);
        quickSortCaller(vec,left,pivot-1);
        quickSortCaller(vec,pivot+1,right);
    }
}
void quickSort(vint &vec)
{
    quickSortCaller(vec,0,vec.size()-1);
}

//Counting Sort
void countingSort(vint &vec)
{
    int maxElt = *max_element(vec.begin(),vec.end());
    vint counter(maxElt+1,0);
    for(int elt : vec)
        counter[elt] += 1;

    for(int x=1;x<counter.size();x++)
        counter[x] += counter[x-1];

        vint result(vec.size());
    for(int x=vec.size()-1;x>=0;x--)
    {
        result[counter[vec[x]]-1] = vec[x];
        counter[vec[x]]--;
    }
    vec = result;
}
int main()
{
    // vint vec = {45, -12, 0, 89, 23, -56, 45, 17, 100, -3, 23, 78, -90, 56, 12, -12};
    vint vec =  {7,9,9,2,6,4,9,8,1,2,5,8,6,5,8,1};
    for(int x : vec) cout<<x<<" "; cout<<endl;
    // insertionSort(vec);
    // heapSort(vec);
    // mergeSort(vec);
    // quickSort(vec);
    countingSort(vec);
    for(int x : vec) cout<<x<<" "; cout<<endl;
}