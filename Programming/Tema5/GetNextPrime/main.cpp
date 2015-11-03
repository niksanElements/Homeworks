#include <iostream>

using namespace std;
int GetNextPrime();

int GetNextPrime()
{
    static unsigned int num = 1;
    bool is_prime = false;
    while(!is_prime)
    {
        if(!is_prime)
            num++;
        is_prime = true;
        for(unsigned i = 2;i*i<=num;i++)
        {
            if(num%i == 0)
            {
                is_prime = false;
                break;
            }
        }
    }
    return num;
}

int main()
{
    for(int i = 0;i < 1000;i++)
        cout << GetNextPrime() << " ";
    return 0;
}
