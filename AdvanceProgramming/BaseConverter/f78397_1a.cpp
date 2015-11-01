#include <iostream>

using namespace std;

int main()
{
    int n = 450;
    int i = 2;
    int counter= 0;
    while(n != 1)
    {
        if(n % i == 0)
        {
            n /= i;
            cout << i << " ";
        }
        else
        {
            i++;
        }
    }
    cout << counter;
}
