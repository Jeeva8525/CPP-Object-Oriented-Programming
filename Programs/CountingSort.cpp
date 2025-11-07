#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int> vint;
void CountingSort(vint &vec)
{
    
    int max_elt = *max_element(vec.begin(),vec.end());
    vint counter(max_elt+1,0);
    for(int p : vec)
        counter[p]++;

    for(int x=1;x<counter.size();x++)
    {
        counter[x] += counter[x-1];
    }
    vint res(vec.size());
    for(int x=vec.size()-1;x>=0;x--)
    {
        res[counter[vec[x]]-1] = vec[x];
        counter[vec[x]]--;
    }
    vec = res;
}
int main()
{
    vint vec = {4,3,6,7,7,3,3,1};
    CountingSort(vec);
    for(int x : vec) cout<<x<<" ";
    cout<<endl;
}