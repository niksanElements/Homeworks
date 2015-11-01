#include <iostream>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    if(n > m)
    {
        n ^= m;
        m ^= n;
        n ^= m;
    }
    int numbers = n;
    int sum = 0;
    while(numbers <= m)
    {
        sum += numbers;
        numbers++;
    }
    cout << sum << " = 1 ";
    int i = 2;
    while(sum > 1)
    {
        if(0 == sum % i)
        {
            cout << " * " << i;
            sum /= i;
        }
        else
        {
            i++;
        }
    }
    return 0;
}
