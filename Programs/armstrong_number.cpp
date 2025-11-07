#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int r=0,n,n1;
    for(int x=0;x<1000;x++)
    {
        r=0;
        n=x;
        while(n>0)
        {
            r+=pow(n%10,3);
            n/=10;
        }
        if (r==x)
            cout<<r<<endl;

    }
}
