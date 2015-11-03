#include <iostream>

using namespace std;

unsigned NumbersOfDevision(unsigned num)
{
    unsigned count = 0;
    unsigned devision = 2;
    unsigned result = 1;
    while(num != 1)
    {
        if(num%devision == 0)
        {
            num /= devision;
            count++;
        }
        else
        {
            result *= (count+1);
            devision++;
            count = 0;
        }
    }
    return result*(count+1);
}

int main()
{
    cout << NumbersOfDevision(4) << endl;

    return 0;
}
