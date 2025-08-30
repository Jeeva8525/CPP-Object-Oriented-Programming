#include <iostream>
using namespace std;
template<typename T>
void swapUsingBinary(T& a,T& b)
{
    //swapping using bitwise xor operation 
    a ^= b;
    b ^= a;
    a ^= b;
}
int main()
{
    int a,b;
    cout<<"Enter two numbers\n";
    cin>>a>>b;
    cout<<"Numbers before swapping"<<endl;
    cout << "A is : " << a << endl;
    cout << "B is : " << b << endl;
    swapUsingBinary(a,b);
    cout<<"Numbers after swapping"<<endl;
    cout << "A is : " << a << endl;
    cout << "B is : " << b << endl;
}
